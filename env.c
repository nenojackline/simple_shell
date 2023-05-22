#include "shell.h"

/**
 * _fnenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _fnenv(fninfopass_t *info)
{
	fnPrintListStr(info->env);
	return (0);
}

/**
 * _fngetenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_fngetenv(fninfopass_t *info, const char *name)
{
	lst_t *node = info->env;
	char *p;

	while (node)
	{
		p = fn_degin_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
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
	if (info->argc != 3)
	{
		_fneputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_fn_setenv(info, info->argv[1], info->argv[2]))
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
	int i;

	if (info->argc == 1)
	{
		_fneputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_fn_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * fnpopulateEnvList - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fnpopulateEnvList(fninfopass_t *info)
{
	lst_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		fnAddNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
