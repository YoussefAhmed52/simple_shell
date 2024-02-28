#include "shell.h"

/**
 * _my_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_history(info_t *info)
{
	list_print(info->history);
	return (0);
}

/**
 * alias_unset - sets alias to string
 * @str: the string alias
 * @info: parameter struct
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_unset(info_t *info, char *str)
{
	char *po, ch;
	int re_turn;

	po = _strchr(str, '=');
	if (!po)
		return (1);
	ch = *po;
	*po = 0;
	re_turn = node_at_index_delete(&(info->alias),
		get_index_of_node(info->alias, node_starts_with_prefix(info->alias, str,
				-1)));
	*po = ch;
	return (re_turn);
}

/**
 * alias_set - sets alias to string
 * @str: the string alias
 * @info: parameter struct
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info_t *info, char *str)
{
	char *po;

	po = _strchr(str, '=');
	if (!po)
		return (1);
	if (!*++po)
		return (alias_unset(info, str));

	alias_unset(info, str);
	return (node_add_end(&(info->alias), str, 0) == NULL);
}

/**
 * alias_print - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_print(list_t *node)
{
	char *po = NULL, *al = NULL;

	if (node)
	{
		po = _strchr(node->str, '=');
		for (al = node->str; al <= po; al++)
			_putchar(*al);
		_putchar('\'');
		_puts(po + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_alias(info_t *info)
{
	int j = 0;
	char *po = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		po = _strchr(info->argv[j], '=');
		if (po)
			alias_set(info, info->argv[j]);
		else
			alias_print(node_starts_with_prefix(info->alias, info->argv[j], '='));
	}

	return (0);
}

