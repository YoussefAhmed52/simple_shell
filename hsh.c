#include "shell.h"

/**
 * _hsh - main shell loop
 * @av: the argument vector from main()
 * @info: the parameter & return info struct
 *
 * Return: 0 on success, 1 on error, or error code
 */
int _hsh(info_t *info, char **av)
{
	ssize_t ret = 0;
	int built_in_ret = 0;

	while (ret != -1 && built_in_ret != -2)
	{
		info_clear(info);
		if (interactive_mode(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		ret = input_get(info);
		if (ret != -1)
		{
			info_set(info, av);
			built_in_ret = find_built_in(info);
			if (built_in_ret == -1)
				cmd_find(info);
		}
		else if (interactive_mode(info))
			_putchar('\n');
		info_free(info, 0);
	}
	write_history(info);
	info_free(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (built_in_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_in_ret);
}

/**
 * find_built_in - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if built in not found,
 *			0 if built in executed successfully,
 *			1 if built in found but not successful,
 *			-2 if built in signals exit()
 */
int find_built_in(info_t *info)
{
	int j, built_in_ret = -1;
	built_in_table built_intbl[] = {
		{"exit", _my_exit},
		{"env", _my_env},
		{"help", _my_help},
		{"history", _my_history},
		{"setenv", _my_envset},
		{"unsetenv", _my_unsetenv},
		{"cd", _my_cd},
		{"alias", _my_alias},
		{NULL, NULL}
	};

	for (j = 0; built_intbl[j].type; j++)
		if (_strcmp(info->argv[0], built_intbl[j].type) == 0)
		{
			info->line_count++;
			built_in_ret = built_intbl[j].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * cmd_find - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmd_find(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delimeter(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = path_find(info, _envget(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		cmd_fork(info);
	}
	else
	{
		if ((interactive_mode(info) || _envget(info, "PATH=")
			|| info->argv[0][0] == '/') && cmd_is(info, info->argv[0]))
			cmd_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			error_print(info, "not found\n");
		}
	}
}

/**
 * cmd_fork - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmd_fork(info_t *info)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			info_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				error_print(info, "Permission denied\n");
		}
	}
}

