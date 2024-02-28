#include "shell.h"

/**
 * *_strncpy - copies a string
 *@src: the source string
 *@dest: the destination string to be copied to
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int it, i;
	char *st = dest;

	it = 0;
	while (src[it] != '\0' && it < n - 1)
	{
		dest[it] = src[it];
		it++;
	}
	if (it < n)
	{
		i = it;
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (st);
}

/**
 * *_strncat - concatenates two strings
 *@src: the second string
 *@dest: the first string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int j, k;
	char *st = dest;

	j = 0;
	k = 0;
	while (dest[j] != '\0')
		j++;
	while (src[k] != '\0' && k < n)
	{
		dest[j] = src[k];
		j++;
		k++;
	}
	if (k < n)
		dest[j] = '\0';
	return (st);
}

/**
 * *_strchr - locates a character in a string
 *@c: the character to look for
 *@s: the string to be parsed
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

