#include "shell.h"

/**
 * fnAddNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @fnstr: fnstr field of node
 * @fnnum: node index used by fnhistory
 *
 * Return: size of list
 */
lst_t *fnAddNode(lst_t **head, const char *fnstr, int fnnum)
{
	lst_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(lst_t));
	if (!new_head)
		return (NULL);
	_fn_memryset((void *)new_head, 0, sizeof(lst_t));
	new_head->fnnum = fnnum;
	if (fnstr)
	{
		new_head->fnstr = _fn_strndup(fnstr);
		if (!new_head->fnstr)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->fnnext = *head;
	*head = new_head;
	return (new_head);
}

/**
 * fnAddNodeEnd - adds a node to the end of the list
 * @head: address of pointer to head node
 * @fnstr: fnstr field of node
 * @fnnum: node index used by fnhistory
 *
 * Return: size of list
 */
lst_t *fnAddNodeEnd(lst_t **head, const char *fnstr, int fnnum)
{
	lst_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(lst_t));
	if (!new_node)
		return (NULL);
	_fn_memryset((void *)new_node, 0, sizeof(lst_t));
	new_node->fnnum = fnnum;
	if (fnstr)
	{
		new_node->fnstr = _fn_strndup(fnstr);
		if (!new_node->fnstr)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->fnnext)
			node = node->fnnext;
		node->fnnext = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * fnPrintListStr - prints only the fnstr element of a lst_t linked list
 * @fnh: pointer to first node
 *
 * Return: size of list
 */
size_t fnPrintListStr(const lst_t *fnh)
{
	size_t fni = 0;

	while (fnh)
	{
		_fn_puts(fnh->fnstr ? fnh->fnstr : "(nil)");
		_fn_puts("\n");
		fnh = fnh->fnnext;
		fni++;
	}
	return (fni);
}

/**
 * fnDeleteNodeAtIndex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int fnDeleteNodeAtIndex(lst_t **head, unsigned int index)
{
	lst_t *node, *prev_node;
	unsigned int fni = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->fnnext;
		free(node->fnstr);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (fni == index)
		{
			prev_node->fnnext = node->fnnext;
			free(node->fnstr);
			free(node);
			return (1);
		}
		fni++;
		prev_node = node;
		node = node->fnnext;
	}
	return (0);
}

/**
 * fnFreeList - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void fnFreeList(lst_t **head_ptr)
{
	lst_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->fnnext;
		free(node->fnstr);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
