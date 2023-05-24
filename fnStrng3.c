#include "shell.h"

/**
 **_fn_strngcpy - copies a string
 *@fndestination: the destination string to be copied to
 *@fnsource: the source string
 *@fnn: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_fn_strngcpy(char *fndestination, char *fnsource, int fnn)
{
	int fni, j;
	char *fns = fndestination;

	fni = 0;
	while (fnsource[fni] != '\0' && fni < fnn - 1)
	{
		fndestination[fni] = fnsource[fni];
		fni++;
	}
	if (fni < fnn)
	{
		j = fni;
		while (j < fnn)
		{
			fndestination[j] = '\0';
			j++;
		}
	}
	return (fns);
}

/**
 **_fn_strngcat - concatenates two strings
 *@fndestination: the first string
 *@fnsource: the second string
 *@fnn: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_fn_strngcat(char *fndestination, char *fnsource, int fnn)
{
	int fni, j;
	char *fns = fndestination;

	fni = 0;
	j = 0;
	while (fndestination[fni] != '\0')
		fni++;
	while (fnsource[j] != '\0' && j < fnn)
	{
		fndestination[fni] = fnsource[j];
		fni++;
		j++;
	}
	if (j < fnn)
		fndestination[fni] = '\0';
	return (fns);
}

/**
 **_fn_strngchr - locates a character in a string
 *@fns: the string to be parsed
 *@fnc: the character to look for
 *Return: (fns) a pointer to the memory area fns
 */
char *_fn_strngchr(char *fns, char fnc)
{
	do {
		if (*fns == fnc)
			return (fns);
	} while (*fns++ != '\0');

	return (NULL);
}
