#include "shell.h"

/**
 * _fnenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _fnenv(fninfopass_t *info)
{
	fnPrintListStr(info->fnenv);
	return (0);
}

/**
 * _fngetenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @fnname: fnenv var fnname
 *
 * Return: the value
 */
char *_fngetenv(fninfopass_t *info, const char *fnname)
{
	lst_t *node = info->fnenv;
	char *fnp;

	while (node)
	{
		fnp = fn_degin_with(node->fnstr, fnname);
		if (fnp && *fnp)
			return (fnp);
		node = node->fnnext;
	}
	return (NULL);
}

/**
 * _fnsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _fnsetenv(fninfopass_t *info)
{
	if (info->fnargc != 3)
	{
		_fneputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_fn_setenv(info, info->fnargv[1], info->fnargv[2]))
		return (0);
	return (1);
}

/**
 * _fnunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _fnunsetenv(fninfopass_t *info)
{
	int fni;

	if (info->fnargc == 1)
	{
		_fneputs("Too few arguements.\n");
		return (1);
	}
	for (fni = 1; fni <= info->fnargc; fni++)
		_fn_unsetenv(info, info->fnargv[fni]);

	return (0);
}

/**
 * fnpopulateEnvList - populates fnenv linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fnpopulateEnvList(fninfopass_t *info)
{
	lst_t *node = NULL;
	size_t fni;

	for (fni = 0; environ[fni]; fni++)
		fnAddNodeEnd(&node, environ[fni], 0);
	info->fnenv = node;
	return (0);
}
