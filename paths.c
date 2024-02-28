#include "shell.h"

/**
 * cmd_is - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cmd_is(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chars_dup - duplicates characters
 * @start: starting index
 * @pathstr: the PATH string
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *chars_dup(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int j = 0, i = 0;

	for (i = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buff[i++] = pathstr[j];
	buff[i] = 0;
	return (buff);
}

/**
 * path_find - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *path_find(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with_haystack(cmd, "./"))
	{
		if (cmd_is(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = chars_dup(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (cmd_is(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}

