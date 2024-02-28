#include "shell.h"

/**
 * _my_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _my_exit(info_t *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_check = _atoierr(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			error_print(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _atoierr(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_cd(info_t *info)
{
	char *si, *dirct, buffer[1024];
	int chdirct_ret;

	si = getcwd(buffer, 1024);
	if (!si)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirct = _envget(info, "HOME=");
		if (!dirct)
			chdirct_ret = chdir((dirct = _envget(info, "PWD=")) ? dirct : "/");
		else
			chdirct_ret = chdir(dirct);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_envget(info, "OLDPWD="))
		{
			_puts(si);
			_putchar('\n');
			return (1);
		}
		_puts(_envget(info, "OLDPWD=")), _putchar('\n');
		chdirct_ret = /* TODO: what should this be? */
			chdir((dirct = _envget(info, "OLDPWD=")) ? dirct : "/");
	}
	else
		chdirct_ret = chdir(info->argv[1]);
	if (chdirct_ret == -1)
	{
		error_print(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_envset(info, "OLDPWD", _envget(info, "PWD="));
		_envset(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _my_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_help(info_t *info)
{
	char **arr_arg;

	arr_arg = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arr_arg); /* temp att_unused workaround */
	return (0);
}

