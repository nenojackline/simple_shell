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
	char *fnp, fnc;
	int fnret;

	fnp = _fn_strngchr(fnstr, '=');
	if (!fnp)
		return (1);
	fnc = *fnp;
	*fnp = 0;
	fnret = fnDeleteNodeAtIndex(&(info->fnalias),
		fnGetNodeIndex(info->fnalias, fnNodeStartsWith(info->fnalias, fnstr, -1)));
	*fnp = fnc;
	return (fnret);
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
	char *fnp;

	fnp = _fn_strngchr(fnstr, '=');
	if (!fnp)
		return (1);
	if (!*++fnp)
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
	char *fnp = NULL, *fna = NULL;

	if (node)
	{
		fnp = _fn_strngchr(node->fnstr, '=');
		for (fna = node->fnstr; fna <= fnp; fna++)
			_fn_putchar(*fna);
		_fn_putchar('\'');
		_fn_puts(fnp + 1);
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
	int fni = 0;
	char *fnp = NULL;
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
	for (fni = 1; info->fnargv[fni]; fni++)
	{
		fnp = _fn_strngchr(info->fnargv[fni], '=');
		if (fnp)
			set_alias(info, info->fnargv[fni]);
		else
			print_alias(fnNodeStartsWith(info->fnalias, info->fnargv[fni], '='));
	}

	return (0);
}
