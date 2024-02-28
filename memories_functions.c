#include "shell.h"

/**
 * _memory_set - fills memory with a constant byte
 *@n: the amount of bytes to be filled
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *Return: (s) a pointer to the memory area s
 */
char *_memory_set(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * f_free - frees a string of strings
 * @pp: string of strings
 */
void f_free(char **pp)
{
	char **c = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(c);
}

/**
 * _re_alloc - reallocates a block of memory
 * @old_size: byte size of previous block
 * @ptr: pointer to previous malloc'ated block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *po;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	po = malloc(new_size);
	if (!po)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		po[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (po);
}

