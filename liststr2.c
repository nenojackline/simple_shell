#include "shell.h"

/**
 * fnListLen - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t fnListLen(const lst_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->fnnext;
		i++;
	}
	return (i);
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
	size_t i = fnListLen(head), j;
	char **strs;
	char *fnstr;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->fnnext, i++)
	{
		fnstr = malloc(_fn_strnlen(node->fnstr) + 1);
		if (!fnstr)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		fnstr = _fn_strncopy(fnstr, node->fnstr);
		strs[i] = fnstr;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * fnPrintLists - prints all elements of a lst_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t fnPrintLists(const lst_t *h)
{
	size_t i = 0;

	while (h)
	{
		_fn_puts(fncnvrtnumber(h->fnnum, 10, 0));
		_fn_putchar(':');
		_fn_putchar(' ');
		_fn_puts(h->fnstr ? h->fnstr : "(nil)");
		_fn_puts("\n");
		h = h->fnnext;
		i++;
	}
	return (i);
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
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->fnnext;
		i++;
	}
	return (-1);
}
