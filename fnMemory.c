#include "shell.h"

/**
 **_fn_memryset - fills memory with a constant byte
 *@fns: the pointer to the memory area
 *@fnb: the byte to fill *fns with
 *@fnn: the amount of bytes to be filled
 *Return: (fns) a pointer to the memory area fns
 */
char *_fn_memryset(char *fns, char fnb, unsigned int fnn)
{
	unsigned int i;

	for (i = 0; i < fnn; i++)
		fns[i] = fnb;
	return (fns);
}

/**
 * fnffree - frees a string of strings
 * @fnpp: string of strings
 */
void fnffree(char **fnpp)
{
	char **a = fnpp;

	if (!fnpp)
		return;
	while (*fnpp)
		free(*fnpp++);
	free(a);
}

/**
 * _fnrealloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @fnold_sz: byte size of previous block
 * @fnnew_sz: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_fnrealloc(void *ptr, unsigned int fnold_sz, unsigned int fnnew_sz)
{
	char *fnp;

	if (!ptr)
		return (malloc(fnnew_sz));
	if (!fnnew_sz)
		return (free(ptr), NULL);
	if (fnnew_sz == fnold_sz)
		return (ptr);

	fnp = malloc(fnnew_sz);
	if (!fnp)
		return (NULL);

	fnold_sz = fnold_sz < fnnew_sz ? fnold_sz : fnnew_sz;
	while (fnold_sz--)
		fnp[fnold_sz] = ((char *)ptr)[fnold_sz];
	free(ptr);
	return (fnp);
}
