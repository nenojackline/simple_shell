#include "shell.h"

/**
 * **fn_strntow - splits a string into words. Repeat delimiters are ignored
 * @fnstr: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **fn_strntow(char *fnstr, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (fnstr == NULL || fnstr[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; fnstr[i] != '\0'; i++)
		if (!fnisdelim(fnstr[i], d) && (fnisdelim(fnstr[i + 1], d) || !fnstr[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (fnisdelim(fnstr[i], d))
			i++;
		k = 0;
		while (!fnisdelim(fnstr[i + k], d) && fnstr[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = fnstr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **fn_strntow2 - splits a string into words
 * @fnstr: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **fn_strntow2(char *fnstr, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (fnstr == NULL || fnstr[0] == 0)
		return (NULL);
	for (i = 0; fnstr[i] != '\0'; i++)
		if ((fnstr[i] != d && fnstr[i + 1] == d) ||
		    (fnstr[i] != d && !fnstr[i + 1]) || fnstr[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (fnstr[i] == d && fnstr[i] != d)
			i++;
		k = 0;
		while (fnstr[i + k] != d && fnstr[i + k] && fnstr[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = fnstr[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
