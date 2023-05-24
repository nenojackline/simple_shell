#include "shell.h"

/**
 * fninteractive - returns true if shell is fninteractive mode
 * @info: struct address
 *
 * Return: 1 if fninteractive mode, 0 otherwise
 */
int fninteractive(fninfopass_t *info)
{
	return (isatty(STDIN_FILENO) && info->fnreadfd <= 2);
}

/**
 * fnisdelim - checks if character is a delimeter
 * @fnc: the char to check
 * @fndelim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int fnisdelim(char fnc, char *fndelim)
{
	while (*fndelim)
		if (*fndelim++ == fnc)
			return (1);
	return (0);
}

/**
 *_fnis_alpha - checks for alphabetic character
 *@fnc: The character to input
 *Return: 1 if fnc is alphabetic, 0 otherwise
 */

int _fnis_alpha(int fnc)
{
	if ((fnc >= 'a' && fnc <= 'z') || (fnc >= 'A' && fnc <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_fnatoi - converts a string to an integer
 *@fns: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _fnatoi(char *fns)
{
	int fni, fnsign = 1, fnflag = 0, fnouput;
	unsigned int result = 0;

	for (fni = 0;  fns[fni] != '\0' && fnflag != 2; fni++)
	{
		if (fns[fni] == '-')
			fnsign *= -1;

		if (fns[fni] >= '0' && fns[fni] <= '9')
		{
			fnflag = 1;
			result *= 10;
			result += (fns[fni] - '0');
		}
		else if (fnflag == 1)
			fnflag = 2;
	}

	if (fnsign == -1)
		fnouput = -result;
	else
		fnouput = result;

	return (fnouput);
}
