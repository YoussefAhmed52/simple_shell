#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *ret_urn;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret_urn = malloc(sizeof(char) * (len += 1));
	if (!ret_urn)
		return (NULL);
	for (len++; len--;)
		ret_urn[len] = *--str;
	return (ret_urn);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int it = 0;

	if (!str)
		return;
	while (str[it] != '\0')
	{
		_putchar(str[it]);
		it++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int it;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || it >= WRITE_BUF_SIZE)
	{
		write(1, buff, it);
		it = 0;
	}
	if (c != BUF_FLUSH)
		buff[it++] = c;
	return (1);
}

