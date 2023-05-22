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
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * fnCheckChain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void fnCheckChain(fninfopass_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
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
		node = fnNodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _fn_strngchr(node->str, '=');
		if (!p)
			return (0);
		p = _fn_strndup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
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

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_fn_strncmp(info->argv[i], "$?"))
		{
			fnReplaceString(&(info->argv[i]),
				_fn_strndup(fncnvrtnumber(info->status, 10, 0)));
			continue;
		}
		if (!_fn_strncmp(info->argv[i], "$$"))
		{
			fnReplaceString(&(info->argv[i]),
				_fn_strndup(fncnvrtnumber(getpid(), 10, 0)));
			continue;
		}
		node = fnNodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			fnReplaceString(&(info->argv[i]),
				_fn_strndup(_fn_strngchr(node->str, '=') + 1));
			continue;
		}
		fnReplaceString(&info->argv[i], _fn_strndup(""));

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
