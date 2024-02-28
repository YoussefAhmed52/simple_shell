#include "shell.h"

/**
 * _my_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _my_env(info_t *info)
{
	print_str_list(info->env);
	return (0);
}

/**
 * _envget - gets the value of an environ variable
 * @name: env var name
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the value
 */
char *_envget(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with_haystack(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _my_envset - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_envset(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_envset(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_unsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * env_list_populate - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env_list_populate(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environment[j]; j++)
		node_add_end(&node, environment[j], 0);
	info->env = node;
	return (0);
}

