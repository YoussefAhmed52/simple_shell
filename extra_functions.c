#include "shell.h"

/**
 * interactive_mode - returns true if shell is interactive_mode
 * @info: structs address
 *
 * Return: 1 if interactive_mode, 0 otherwise
 */
int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_is_alpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int j, sign = 1, fl = 0, out_put;
	unsigned int res = 0;

	for (j = 0;  s[j] != '\0' && fl != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (s[j] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (sign == -1)
		out_put = -res;
	else
		out_put = res;

	return (out_put);
}

