#include "shell.h"

/**
 * _fnhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _fnhistory(fninfopass_t *info)
{
	fnPrintLists(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(fninfopass_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _fn_strngchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = fnDeleteNodeAtIndex(&(info->alias),
		fnGetNodeIndex(info->alias, fnNodeStartsWith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(fninfopass_t *info, char *str)
{
	char *p;

	p = _fn_strngchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (fnAddNodeEnd(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(lst_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _fn_strngchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_fn_putchar(*a);
		_fn_putchar('\'');
		_fn_puts(p + 1);
		_fn_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _fnalias - mimics the alias fnbuiltin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _fnalias(fninfopass_t *info)
{
	int i = 0;
	char *p = NULL;
	lst_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _fn_strngchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(fnNodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}
