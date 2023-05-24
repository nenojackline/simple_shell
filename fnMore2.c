#include "shell.h"

/**
 * _fnerratoi - converts a string to an integer
 * @fns: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _fnerratoi(char *fns)
{
	int fni = 0;
	unsigned long int result = 0;

	if (*fns == '+')
		fns++;  /* TODO: why does this make main return 255? */
	for (fni = 0;  fns[fni] != '\0'; fni++)
	{
		if (fns[fni] >= '0' && fns[fni] <= '9')
		{
			result *= 10;
			result += (fns[fni] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * fnprnterr - prints an error message
 * @info: the parameter & return info struct
 * @fnestr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void fnprnterr(fninfopass_t *info, char *fnestr)
{
	_fneputs(info->fnfname);
	_fneputs(": ");
	fnprntd(info->fnline_count, STDERR_FILENO);
	_fneputs(": ");
	_fneputs(info->fnargv[0]);
	_fneputs(": ");
	_fneputs(fnestr);
}

/**
 * fnprntd - function prints a decimal (integer) number (base 10)
 * @fninput: the fninput
 * @fnfd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int fnprntd(int fninput, int fnfd)
{
	int (*__putchar)(char) = _fn_putchar;
	int fni, count = 0;
	unsigned int _abs_, current;

	if (fnfd == STDERR_FILENO)
		__putchar = _fneputschar;
	if (fninput < 0)
	{
		_abs_ = -fninput;
		__putchar('-');
		count++;
	}
	else
		_abs_ = fninput;
	current = _abs_;
	for (fni = 1000000000; fni > 1; fni /= 10)
	{
		if (_abs_ / fni)
		{
			__putchar('0' + current / fni);
			count++;
		}
		current %= fni;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * fncnvrtnumber - converter function, a clone of itoa
 * @fnnum: number
 * @fnbase: fnbase
 * @fnflags: argument fnflags
 *
 * Return: string
 */
char *fncnvrtnumber(long int fnnum, int fnbase, int fnflags)
{
	static char *fnarray;
	static char fnbuffer[50];
	char fnsign = 0;
	char *fnnptr;
	unsigned long fnn = fnnum;

	if (!(fnflags & CVNT_UNSD) && fnnum < 0)
	{
		fnn = -fnnum;
		fnsign = '-';

	}
	fnarray = fnflags & CVNT_LWCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	fnnptr = &fnbuffer[49];
	*fnnptr = '\0';

	do	{
		*--fnnptr = fnarray[fnn % fnbase];
		fnn /= fnbase;
	} while (fnn != 0);

	if (fnsign)
		*--fnnptr = fnsign;
	return (fnnptr);
}

/**
 * fndelcomments - function replaces first instance of '#' with '\0'
 * @fnbuf: address of the string to modify
 *
 * Return: Always 0;
 */
void fndelcomments(char *fnbuf)
{
	int fni;

	for (fni = 0; fnbuf[fni] != '\0'; fni++)
		if (fnbuf[fni] == '#' && (!fni || fnbuf[fni - 1] == ' '))
		{
			fnbuf[fni] = '\0';
			break;
		}
}
