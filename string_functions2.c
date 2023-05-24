#include "shell.h"

/**
 * _fn_strncopy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_fn_strncopy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _fn_strndup - duplicates a string
 * @fnstr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_fn_strndup(const char *fnstr)
{
	int length = 0;
	char *ret;

	if (fnstr == NULL)
		return (NULL);
	while (*fnstr++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--fnstr;
	return (ret);
}

/**
 *_fn_puts - prints an input string
 *@fnstr: the string to be printed
 *
 * Return: Nothing
 */
void _fn_puts(char *fnstr)
{
	int i = 0;

	if (!fnstr)
		return;
	while (fnstr[i] != '\0')
	{
		_fn_putchar(fnstr[i]);
		i++;
	}
}

/**
 * _fn_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _fn_putchar(char c)
{
	static int i;
	static char buf[W_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= W_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}
