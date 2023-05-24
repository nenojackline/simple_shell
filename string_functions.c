#include "shell.h"

/**
 * _fn_strnlen - returns the length of a string
 * @fns: the string whose length to check
 *
 * Return: integer length of string
 */
int _fn_strnlen(char *fns)
{
	int fni = 0;

	if (!fns)
		return (0);

	while (*fns++)
		fni++;
	return (fni);
}

/**
 * _fn_strncmp - performs lexicogarphic comparison of two strangs.
 * @fns1: the first strang
 * @fns2: the second strang
 *
 * Return: negative if fns1 < fns2, positive if fns1 > fns2, zero if fns1 == fns2
 */
int _fn_strncmp(char *fns1, char *fns2)
{
	while (*fns1 && *fns2)
	{
		if (*fns1 != *fns2)
			return (*fns1 - *fns2);
		fns1++;
		fns2++;
	}
	if (*fns1 == *fns2)
		return (0);
	else
		return (*fns1 < *fns2 ? -1 : 1);
}

/**
 * fn_degin_with - checks if fnneedle starts with fnhaystack
 * @fnhaystack: string to search
 * @fnneedle: the substring to find
 *
 * Return: address of fnnext char of fnhaystack or NULL
 */
char *fn_degin_with(const char *fnhaystack, const char *fnneedle)
{
	while (*fnneedle)
		if (*fnneedle++ != *fnhaystack++)
			return (NULL);
	return ((char *)fnhaystack);
}

/**
 * _fn_strncat - concatenates two strings
 * @fndest: the destination buffer
 * @fnsource: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_fn_strncat(char *fndest, char *fnsource)
{
	char *fnret = fndest;

	while (*fndest)
		fndest++;
	while (*fnsource)
		*fndest++ = *fnsource++;
	*fndest = *fnsource;
	return (fnret);
}
