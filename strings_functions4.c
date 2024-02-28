#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @d: the delimeter string
 * @str: the input string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, num_words = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimeter(str[i], d) && (is_delimeter(str[i + 1], d) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	st = malloc((1 + num_words) * sizeof(char *));
	if (!st)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimeter(str[i], d))
			i++;
		k = 0;
		while (!is_delimeter(str[i + k], d) && str[i + k])
			k++;
		st[j] = malloc((k + 1) * sizeof(char));
		if (!st[j])
		{
			for (k = 0; k < j; k++)
				free(st[k]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			st[j][m] = str[i++];
		st[j][m] = 0;
	}
	st[j] = NULL;
	return (st);
}

/**
 * **strtow2 - splits a string into words
 * @d: the delimeter
 * @str: the input string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, num_words = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	st = malloc((1 + num_words) * sizeof(char *));
	if (!st)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		st[j] = malloc((k + 1) * sizeof(char));
		if (!st[j])
		{
			for (k = 0; k < j; k++)
				free(st[k]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			st[j][m] = str[i++];
		st[j][m] = 0;
	}
	st[j] = NULL;
	return (st);
}

