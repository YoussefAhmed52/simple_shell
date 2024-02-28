#include "shell.h"

/**
 * _atoierr - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _atoierr(char *s)
{
	int j = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			res *= 10;
			res += (s[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * error_print - prints an error message
 * @estr: string containing specified error type
 * @info: the parameter & return info struct
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void error_print(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	dec_print(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * dec_print - function prints a decimal (integer) number (base 10)
 * @fd: the filedescriptor to write to
 * @input: the input
 *
 * Return: number of characters printed
 */
int dec_print(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, counter = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			counter++;
		}
		current %= j;
	}
	__putchar('0' + current);
	counter++;

	return (counter);
}

/**
 * number_convert - converter function, a clone of itoa
 * @flags: argument flags
 * @base: base
 * @num: number
 *
 * Return: string
 */
char *number_convert(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *p;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = arr[number % base];
		number /= base;
	} while (number != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * comments_removal - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void comments_removal(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}

