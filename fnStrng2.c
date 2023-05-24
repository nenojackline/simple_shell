#include "shell.h"

/**
 * _fn_strncopy - copies a string
 * @fndestination: the destination
 * @fnsource: the source
 *
 * Return: pointer to destination
 */
char *_fn_strncopy(char *fndestination, char *fnsource)
{
	int fni = 0;

	if (fndestination == fnsource || fnsource == 0)
		return (fndestination);
	while (fnsource[fni])
	{
		fndestination[fni] = fnsource[fni];
		fni++;
	}
	fndestination[fni] = 0;
	return (fndestination);
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
	char *fnret;

	if (fnstr == NULL)
		return (NULL);
	while (*fnstr++)
		length++;
	fnret = malloc(sizeof(char) * (length + 1));
	if (!fnret)
		return (NULL);
	for (length++; length--;)
		fnret[length] = *--fnstr;
	return (fnret);
}

/**
 *_fn_puts - prints an input string
 *@fnstr: the string to be printed
 *
 * Return: Nothing
 */
void _fn_puts(char *fnstr)
{
	int fni = 0;

	if (!fnstr)
		return;
	while (fnstr[fni] != '\0')
	{
		_fn_putchar(fnstr[fni]);
		fni++;
	}
}

/**
 * _fn_putchar - writes the character fnc to stdout
 * @fnc: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _fn_putchar(char fnc)
{
	static int fni;
	static char buf[W_BUFFER_SIZE];

	if (fnc == BUFFER_FLUSH || fni >= W_BUFFER_SIZE)
	{
		write(1, buf, fni);
		fni = 0;
	}
	if (fnc != BUFFER_FLUSH)
		buf[fni++] = fnc;
	return (1);
}
