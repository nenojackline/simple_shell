#include "shell.h"

/**
 * _fnhistory - displays the fnhistory list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _fnhistory(fninfopass_t *info)
{
	fnPrintLists(info->fnhistory);
	return (0);
}

/**
 * unset_alias - sets fnalias to string
 * @info: parameter struct
 * @fnstr: the string fnalias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(fninfopass_t *info, char *fnstr)
{
	char *p, c;
	int ret;

	p = _fn_strngchr(fnstr, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = fnDeleteNodeAtIndex(&(info->fnalias),
		fnGetNodeIndex(info->fnalias, fnNodeStartsWith(info->fnalias, fnstr, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets fnalias to string
 * @info: parameter struct
 * @fnstr: the string fnalias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(fninfopass_t *info, char *fnstr)
{
	char *p;

	p = _fn_strngchr(fnstr, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, fnstr));

	unset_alias(info, fnstr);
	return (fnAddNodeEnd(&(info->fnalias), fnstr, 0) == NULL);
}

/**
 * print_alias - prints an fnalias string
 * @node: the fnalias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(lst_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _fn_strngchr(node->fnstr, '=');
		for (a = node->fnstr; a <= p; a++)
			_fn_putchar(*a);
		_fn_putchar('\'');
		_fn_puts(p + 1);
		_fn_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _fnalias - mimics the fnalias fnbuiltin (man fnalias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _fnalias(fninfopass_t *info)
{
	int i = 0;
	char *p = NULL;
	lst_t *node = NULL;

	if (info->fnargc == 1)
	{
		node = info->fnalias;
		while (node)
		{
			print_alias(node);
			node = node->fnnext;
		}
		return (0);
	}
	for (i = 1; info->fnargv[i]; i++)
	{
		p = _fn_strngchr(info->fnargv[i], '=');
		if (p)
			set_alias(info, info->fnargv[i]);
		else
			print_alias(fnNodeStartsWith(info->fnalias, info->fnargv[i], '='));
	}

	return (0);
}
