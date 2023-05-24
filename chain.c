#include "shell.h"

/**
 * fnIsChain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int fnIsChain(fninfopass_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->fncmd_buf_type = FN_COMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->fncmd_buf_type = FN_COMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->fncmd_buf_type = FN_COMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * fnCheckChain - checks we should continue chaining based on last fnstatus
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void fnCheckChain(fninfopass_t *info, char *buf,
size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->fncmd_buf_type == FN_COMD_AND)
	{
		if (info->fnstatus)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->fncmd_buf_type == FN_COMD_OR)
	{
		if (!info->fnstatus)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * fnReplaceAlias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int fnReplaceAlias(fninfopass_t *info)
{
	int i;
	lst_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = fnNodeStartsWith(info->fnalias, info->fnargv[0], '=');
		if (!node)
			return (0);
		free(info->fnargv[0]);
		p = _fn_strngchr(node->fnstr, '=');
		if (!p)
			return (0);
		p = _fn_strndup(p + 1);
		if (!p)
			return (0);
		info->fnargv[0] = p;
	}
	return (1);
}

/**
 * fnReplaceVars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int fnReplaceVars(fninfopass_t *info)
{
	int i = 0;
	lst_t *node;

	for (i = 0; info->fnargv[i]; i++)
	{
		if (info->fnargv[i][0] != '$' || !info->fnargv[i][1])
			continue;

		if (!_fn_strncmp(info->fnargv[i], "$?"))
		{
			fnReplaceString(&(info->fnargv[i]),
				_fn_strndup(fncnvrtnumber(info->fnstatus, 10, 0)));
			continue;
		}
		if (!_fn_strncmp(info->fnargv[i], "$$"))
		{
			fnReplaceString(&(info->fnargv[i]),
				_fn_strndup(fncnvrtnumber(getpid(), 10, 0)));
			continue;
		}
		node = fnNodeStartsWith(info->fnenv, &info->fnargv[i][1], '=');
		if (node)
		{
			fnReplaceString(&(info->fnargv[i]),
				_fn_strndup(_fn_strngchr(node->fnstr, '=') + 1));
			continue;
		}
		fnReplaceString(&info->fnargv[i], _fn_strndup(""));

	}
	return (0);
}

/**
 * fnReplaceString - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int fnReplaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
