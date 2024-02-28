#include "shell.h"

/**
 * list_length - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * convert_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = list_length(head), i;
	char **strs;
	char *str;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (i = 0; i < j; i++)
				free(strs[i]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 * list_print - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_print(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(number_convert(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with_prefix - returns node whose string starts with prefix
 * @c: the next character after prefix to match
 * @node: pointer to list head
 * @prefix: string to match
 *
 * Return: match node or null
 */
list_t *node_starts_with_prefix(list_t *node, char *prefix, char c)
{
	char *po = NULL;

	while (node)
	{
		po = starts_with_haystack(node->str, prefix);
		if (po && ((c == -1) || (*po == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_index_of_node - gets the index of a node
 * @node: pointer to the node
 * @head: pointer to list head
 *
 * Return: index of node or -1
 */
ssize_t get_index_of_node(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}

