#include "shell.h"

/**
 * fnListLen - determines length of linked list
 * @fnh: pointer to first node
 *
 * Return: size of list
 */
size_t fnListLen(const lst_t *fnh)
{
	size_t fni = 0;

	while (fnh)
	{
		fnh = fnh->fnnext;
		fni++;
	}
	return (fni);
}

/**
 * fnListToStrgs - returns an array of strings of the list->fnstr
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **fnListToStrgs(lst_t *head)
{
	lst_t *node = head;
	size_t fni = fnListLen(head), fnj;
	char **strs;
	char *fnstr;

	if (!head || !fni)
		return (NULL);
	strs = malloc(sizeof(char *) * (fni + 1));
	if (!strs)
		return (NULL);
	for (fni = 0; node; node = node->fnnext, fni++)
	{
		fnstr = malloc(_fn_strnlen(node->fnstr) + 1);
		if (!fnstr)
		{
			for (fnj = 0; fnj < fni; fnj++)
				free(strs[fnj]);
			free(strs);
			return (NULL);
		}

		fnstr = _fn_strncopy(fnstr, node->fnstr);
		strs[fni] = fnstr;
	}
	strs[fni] = NULL;
	return (strs);
}


/**
 * fnPrintLists - prints all elements of a lst_t linked list
 * @fnh: pointer to first node
 *
 * Return: size of list
 */
size_t fnPrintLists(const lst_t *fnh)
{
	size_t fni = 0;

	while (fnh)
	{
		_fn_puts(fncnvrtnumber(fnh->fnnum, 10, 0));
		_fn_putchar(':');
		_fn_putchar(' ');
		_fn_puts(fnh->fnstr ? fnh->fnstr : "(nil)");
		_fn_puts("\n");
		fnh = fnh->fnnext;
		fni++;
	}
	return (fni);
}

/**
 * fnNodeStartsWith - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the fnnext character after prefix to match
 *
 * Return: match node or null
 */
lst_t *fnNodeStartsWith(lst_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = fn_degin_with(node->fnstr, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->fnnext;
	}
	return (NULL);
}

/**
 * fnGetNodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t fnGetNodeIndex(lst_t *head, lst_t *node)
{
	size_t fni = 0;

	while (head)
	{
		if (head == node)
			return (fni);
		head = head->fnnext;
		fni++;
	}
	return (-1);
}
