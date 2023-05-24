#include "shell.h"

/**
 * fnIsChain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @fnbuf: the char buffer
 * @fnp: address of current position in fnbuf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int fnIsChain(fninfopass_t *info, char *fnbuf, size_t *fnp)
{
	size_t fnj = *fnp;

	if (fnbuf[fnj] == '|' && fnbuf[fnj + 1] == '|')
	{
		fnbuf[fnj] = 0;
		fnj++;
		info->fncmd_buf_type = FN_COMD_OR;
	}
	else if (fnbuf[fnj] == '&' && fnbuf[fnj + 1] == '&')
	{
		fnbuf[fnj] = 0;
		fnj++;
		info->fncmd_buf_type = FN_COMD_AND;
	}
	else if (fnbuf[fnj] == ';') /* found end of this command */
	{
		fnbuf[fnj] = 0; /* replace semicolon with null */
		info->fncmd_buf_type = FN_COMD_CHAIN;
	}
	else
		return (0);
	*fnp = fnj;
	return (1);
}

/**
 * fnCheckChain - checks we should continue chaining based on last fnstatus
 * @info: the parameter struct
 * @fnbuf: the char buffer
 * @fnp: address of current position in fnbuf
 * @fni: starting position in fnbuf
 * @fnlen: length of fnbuf
 *
 * Return: Void
 */
void fnCheckChain(fninfopass_t *info, char *fnbuf,
size_t *fnp, size_t fni, size_t fnlen)
{
	size_t fnj = *fnp;

	if (info->fncmd_buf_type == FN_COMD_AND)
	{
		if (info->fnstatus)
		{
			fnbuf[fni] = 0;
			fnj = fnlen;
		}
	}
	if (info->fncmd_buf_type == FN_COMD_OR)
	{
		if (!info->fnstatus)
		{
			fnbuf[fni] = 0;
			fnj = fnlen;
		}
	}

	*fnp = fnj;
}

/**
 * fnReplaceAlias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int fnReplaceAlias(fninfopass_t *info)
{
	int fni;
	lst_t *node;
	char *fnp;

	for (fni = 0; fni < 10; fni++)
	{
		node = fnNodeStartsWith(info->fnalias, info->fnargv[0], '=');
		if (!node)
			return (0);
		free(info->fnargv[0]);
		fnp = _fn_strngchr(node->fnstr, '=');
		if (!fnp)
			return (0);
		fnp = _fn_strndup(fnp + 1);
		if (!fnp)
			return (0);
		info->fnargv[0] = fnp;
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
	int fni = 0;
	lst_t *node;

	for (fni = 0; info->fnargv[fni]; fni++)
	{
		if (info->fnargv[fni][0] != '$' || !info->fnargv[fni][1])
			continue;

		if (!_fn_strncmp(info->fnargv[fni], "$?"))
		{
			fnReplaceString(&(info->fnargv[fni]),
				_fn_strndup(fncnvrtnumber(info->fnstatus, 10, 0)));
			continue;
		}
		if (!_fn_strncmp(info->fnargv[fni], "$$"))
		{
			fnReplaceString(&(info->fnargv[fni]),
				_fn_strndup(fncnvrtnumber(getpid(), 10, 0)));
			continue;
		}
		node = fnNodeStartsWith(info->fnenv, &info->fnargv[fni][1], '=');
		if (node)
		{
			fnReplaceString(&(info->fnargv[fni]),
				_fn_strndup(_fn_strngchr(node->fnstr, '=') + 1));
			continue;
		}
		fnReplaceString(&info->fnargv[fni], _fn_strndup(""));

	}
	return (0);
}

/**
 * fnReplaceString - replaces string
 * @fnold: address of fnold string
 * @fnnew: fnnew string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int fnReplaceString(char **fnold, char *fnnew)
{
	free(*fnold);
	*fnold = fnnew;
	return (1);
}
