#include "shell.h"

/**
 * fnget_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **fnget_environ(fninfopass_t *info)
{
	if (!info->environ || info->fnenv_changed)
	{
		info->environ = fnListToStrgs(info->fnenv);
		info->fnenv_changed = 0;
	}

	return (info->environ);
}

/**
 * _fn_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @fnvar: the string fnenv fnvar property
 */
int _fn_unsetenv(fninfopass_t *info, char *fnvar)
{
	lst_t *node = info->fnenv;
	size_t fni = 0;
	char *fnp;

	if (!node || !fnvar)
		return (0);

	while (node)
	{
		fnp = fn_degin_with(node->fnstr, fnvar);
		if (fnp && *fnp == '=')
		{
			info->fnenv_changed = fnDeleteNodeAtIndex(&(info->fnenv), fni);
			fni = 0;
			node = info->fnenv;
			continue;
		}
		node = node->fnnext;
		fni++;
	}
	return (info->fnenv_changed);
}

/**
 * _fn_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @fnvar: the string fnenv fnvar property
 * @fnvalue: the string fnenv fnvar fnvalue
 *  Return: Always 0
 */
int _fn_setenv(fninfopass_t *info, char *fnvar, char *fnvalue)
{
	char *buf = NULL;
	lst_t *node;
	char *fnp;

	if (!fnvar || !fnvalue)
		return (0);

	buf = malloc(_fn_strnlen(fnvar) + _fn_strnlen(fnvalue) + 2);
	if (!buf)
		return (1);
	_fn_strncopy(buf, fnvar);
	_fn_strncat(buf, "=");
	_fn_strncat(buf, fnvalue);
	node = info->fnenv;
	while (node)
	{
		fnp = fn_degin_with(node->fnstr, fnvar);
		if (fnp && *fnp == '=')
		{
			free(node->fnstr);
			node->fnstr = buf;
			info->fnenv_changed = 1;
			return (0);
		}
		node = node->fnnext;
	}
	fnAddNodeEnd(&(info->fnenv), buf, 0);
	free(buf);
	info->fnenv_changed = 1;
	return (0);
}
