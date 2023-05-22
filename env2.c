#include "shell.h"

/**
 * fnget_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **fnget_environ(fninfopass_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = fnListToStrgs(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _fn_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _fn_unsetenv(fninfopass_t *info, char *var)
{
	lst_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = fn_degin_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = fnDeleteNodeAtIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _fn_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _fn_setenv(fninfopass_t *info, char *var, char *value)
{
	char *buf = NULL;
	lst_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_fn_strnlen(var) + _fn_strnlen(value) + 2);
	if (!buf)
		return (1);
	_fn_strncopy(buf, var);
	_fn_strncat(buf, "=");
	_fn_strncat(buf, value);
	node = info->env;
	while (node)
	{
		p = fn_degin_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	fnAddNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
