#include "shell.h"

/**
 * buf_input- buffers chained commands
 * @len: address of len var
 * @info: parameter struct
 * @buf: address of buffer
 *
 * Return: bytes read
 */
ssize_t buf_input(info_t *info, char **buf, size_t *len)
{
	ssize_t ro = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*b_free((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_Handler);
#if USE_GETLINE
		ro = get_line(buf, &len_p, stdin);
#else
		ro = _get_line(info, buf, &len_p);
#endif
		if (ro > 0)
		{
			if ((*buf)[ro - 1] == '\n')
			{
				(*buf)[ro - 1] = '\0'; /* remove trailing newline */
				ro--;
			}
			info->linecount_flag = 1;
			comments_removal(*buf);
			history_list_build(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = ro;
				info->cmd_buf = buf;
			}
		}
	}
	return (ro);
}

/**
 * input_get - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t input_get(info_t *info)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t j, i, len;
	ssize_t ro = 0;
	char **buf_p = &(info->arg), *po;

	_putchar(BUF_FLUSH);
	ro = buf_input(info, &buff, &len);
	if (ro == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		i = j; /* init new iterator to current buf position */
		po = buff + i; /* get pointer for return */

		chain_check(info, buff, &i, j, len);
		while (i < len) /* iterate to semicolon or end */
		{
			if (_chain(info, buff, &i))
				break;
			i++;
		}

		j = i + 1; /* increment past nulled ';'' */
		if (j >= len) /* reached end of buffer? */
		{
			j = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = po; /* pass back pointer to current command position */
		return (_strlen(po)); /* return length of current command */
	}

	*buf_p = buff; /* else not a chain, pass back buffer from _get_line */
	return (ro); /* return length of buffer from _get_line */
}

/**
 * buf_read - reads a buffer
 * @i: size
 * @info: parameter struct
 * @buf: buffer
 *
 * Return: r
 */
ssize_t buf_read(info_t *info, char *buf, size_t *i)
{
	ssize_t ro = 0;

	if (*i)
		return (0);
	ro = read(info->readfd, buf, READ_BUF_SIZE);
	if (ro >= 0)
		*i = ro;
	return (ro);
}

/**
 * _get_line - gets the next line of input from STDIN
 * @length: size of preallocated ptr buffer if not NULL
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 *
 * Return: s
 */
int _get_line(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t j, leng;
	size_t i;
	ssize_t ro = 0, si = 0;
	char *po = NULL, *new_p = NULL, *ch;

	po = *ptr;
	if (po && length)
		si = *length;
	if (j == leng)
		j = leng = 0;

	ro = buf_read(info, buff, &leng);
	if (ro == -1 || (ro == 0 && leng == 0))
		return (-1);

	ch = _strchr(buff + j, '\n');
	i = ch ? 1 + (unsigned int)(ch - buff) : leng;
	new_p = _re_alloc(po, si, si ? si + i : i + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (po ? free(po), -1 : -1);

	if (si)
		_strncat(new_p, buff + j, i - j);
	else
		_strncpy(new_p, buff + j, i - j + 1);

	si += i - j;
	j = i;
	po = new_p;

	if (length)
		*length = si;
	*ptr = po;
	return (si);
}

/**
 * sigint_Handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

