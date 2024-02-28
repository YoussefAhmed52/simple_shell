#include "shell.h"

/**
 * _chain - test if current char in buffer is a chain delimeter
 * @p: address of current position in buffer
 * @info: the parameter struct
 * @buf: the char buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chain_check - checks we should continue chaining based on last status
 * @i: starting position in buffer
 * @len: length of buffer
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buffer
 *
 *
 * Return: Void
 */
void chain_check(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * alias_replace - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_replace(info_t *info)
{
	int j;
	list_t *node;
	char *po;

	for (j = 0; j < 10; j++)
	{
		node = node_starts_with_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		po = _strchr(node->str, '=');
		if (!po)
			return (0);
		po = _strdup(po + 1);
		if (!po)
			return (0);
		info->argv[0] = po;
	}
	return (1);
}

/**
 * vars_replace - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_replace(info_t *info)
{
	int j = 0;
	list_t *node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			string_replace(&(info->argv[j]),
				_strdup(number_convert(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			string_replace(&(info->argv[j]),
				_strdup(number_convert(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with_prefix(info->env, &info->argv[j][1], '=');
		if (node)
		{
			string_replace(&(info->argv[j]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		string_replace(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * string_replace - replaces string
 * @new: new string
 * @old: address of old string
 *

 * Return: 1 if replaced, 0 otherwise
 */
int string_replace(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

