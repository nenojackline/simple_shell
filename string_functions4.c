#include "shell.h"

/**
 * **fn_strntow - splits a string into words. Repeat delimiters are ignored
 * @fnstr: the input string
 * @fnd: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **fn_strntow(char *fnstr, char *fnd)
{
	int fni, fnj, fnk, fnm, numwords = 0;
	char **s;

	if (fnstr == NULL || fnstr[0] == 0)
		return (NULL);
	if (!fnd)
		fnd = " ";
	for (fni = 0; fnstr[fni] != '\0'; fni++)
		if (!fnisdelim(fnstr[fni], fnd) && (fnisdelim(fnstr[fni + 1], fnd)
			 || !fnstr[fni + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (fni = 0, fnj = 0; fnj < numwords; fnj++)
	{
		while (fnisdelim(fnstr[fni], fnd))
			fni++;
		fnk = 0;
		while (!fnisdelim(fnstr[fni + fnk], fnd) && fnstr[fni + fnk])
			fnk++;
		s[fnj] = malloc((fnk + 1) * sizeof(char));
		if (!s[fnj])
		{
			for (fnk = 0; fnk < fnj; fnk++)
				free(s[fnk]);
			free(s);
			return (NULL);
		}
		for (fnm = 0; fnm < fnk; fnm++)
			s[fnj][fnm] = fnstr[fni++];
		s[fnj][fnm] = 0;
	}
	s[fnj] = NULL;
	return (s);
}

/**
 * **fn_strntow2 - splits a string into words
 * @fnstr: the input string
 * @fnd: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **fn_strntow2(char *fnstr, char fnd)
{
	int fni, fnj, fnk, fnm, numwords = 0;
	char **s;

	if (fnstr == NULL || fnstr[0] == 0)
		return (NULL);
	for (fni = 0; fnstr[fni] != '\0'; fni++)
		if ((fnstr[fni] != fnd && fnstr[fni + 1] == fnd) ||
		    (fnstr[fni] != fnd && !fnstr[fni + 1]) || fnstr[fni + 1] == fnd)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (fni = 0, fnj = 0; fnj < numwords; fnj++)
	{
		while (fnstr[fni] == fnd && fnstr[fni] != fnd)
			fni++;
		fnk = 0;
		while (fnstr[fni + fnk] != fnd && fnstr[fni + fnk] &&
			fnstr[fni + fnk] != fnd)
			fnk++;
		s[fnj] = malloc((fnk + 1) * sizeof(char));
		if (!s[fnj])
		{
			for (fnk = 0; fnk < fnj; fnk++)
				free(s[fnk]);
			free(s);
			return (NULL);
		}
		for (fnm = 0; fnm < fnk; fnm++)
			s[fnj][fnm] = fnstr[fni++];
		s[fnj][fnm] = 0;
	}
	s[fnj] = NULL;
	return (s);
}
