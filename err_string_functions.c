#include "shell.h"

/**
 *_fneputs - prints an input string
 * @fnstr: the string to be printed
 *
 * Return: Nothing
 */
void _fneputs(char *fnstr)
{
	int i = 0;

	if (!fnstr)
		return;
	while (fnstr[i] != '\0')
	{
		_fneputschar(fnstr[i]);
		i++;
	}
}

/**
 * _fneputschar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _fneputschar(char c)
{
	static int i;
	static char buf[W_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= W_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _fneputsfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _fneputsfd(char c, int fd)
{
	static int i;
	static char buf[W_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= W_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_fn_putsfd - prints an input string
 * @fnstr: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _fn_putsfd(char *fnstr, int fd)
{
	int i = 0;

	if (!fnstr)
		return (0);
	while (*fnstr)
	{
		i += _fneputsfd(*fnstr++, fd);
	}
	return (i);
}
