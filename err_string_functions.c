#include "shell.h"

/**
 *_fneputs - prints an input string
 * @fnstr: the string to be printed
 *
 * Return: Nothing
 */
void _fneputs(char *fnstr)
{
	int fni = 0;

	if (!fnstr)
		return;
	while (fnstr[fni] != '\0')
	{
		_fneputschar(fnstr[fni]);
		fni++;
	}
}

/**
 * _fneputschar - writes the character fnc to stderr
 * @fnc: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _fneputschar(char fnc)
{
	static int fni;
	static char fnbuf[W_BUFFER_SIZE];

	if (fnc == BUFFER_FLUSH || fni >= W_BUFFER_SIZE)
	{
		write(2, fnbuf, fni);
		fni = 0;
	}
	if (fnc != BUFFER_FLUSH)
		fnbuf[fni++] = fnc;
	return (1);
}

/**
 * _fneputsfd - writes the character fnc to given fnfd
 * @fnc: The character to print
 * @fnfd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _fneputsfd(char fnc, int fnfd)
{
	static int fni;
	static char fnbuf[W_BUFFER_SIZE];

	if (fnc == BUFFER_FLUSH || fni >= W_BUFFER_SIZE)
	{
		write(fnfd, fnbuf, fni);
		fni = 0;
	}
	if (fnc != BUFFER_FLUSH)
		fnbuf[fni++] = fnc;
	return (1);
}

/**
 *_fn_putsfd - prints an input string
 * @fnstr: the string to be printed
 * @fnfd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _fn_putsfd(char *fnstr, int fnfd)
{
	int fni = 0;

	if (!fnstr)
		return (0);
	while (*fnstr)
	{
		fni += _fneputsfd(*fnstr++, fnfd);
	}
	return (fni);
}
