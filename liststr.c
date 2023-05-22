#include "shell.h"

/**
 * fnAddNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
lst_t *fnAddNode(lst_t **head, const char *str, int num)
{
	lst_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(lst_t));
	if (!new_head)
		return (NULL);
	_fn_memryset((void *)new_head, 0, sizeof(lst_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _fn_strndup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * fnAddNodeEnd - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
lst_t *fnAddNodeEnd(lst_t **head, const char *str, int num)
{
	lst_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(lst_t));
	if (!new_node)
		return (NULL);
	_fn_memryset((void *)new_node, 0, sizeof(lst_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _fn_strndup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * fnPrintListStr - prints only the str element of a lst_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t fnPrintListStr(const lst_t *h)
{
	size_t i = 0;

	while (h)
	{
		_fn_puts(h->str ? h->str : "(nil)");
		_fn_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
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
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
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
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
