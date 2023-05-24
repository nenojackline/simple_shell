#include "shell.h"

/**
 * fn_is_command - determines if a file is an executable command
 * @info: the info struct
 * @fnpath: fnpath to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int fn_is_command(fninfopass_t *info, char *fnpath)
{
	struct stat st;

	(void)info;
	if (!fnpath || stat(fnpath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * fn_duplicate_chars - duplicates characters
 * @fnpathstr: the PATH string
 * @fnstart: starting index
 * @fnstop: stopping index
 *
 * Return: pointer to new buffer
 */
char *fn_duplicate_chars(char *fnpathstr, int fnstart, int fnstop)
{
	static char fnbuf[1024];
	int fni = 0, fnk = 0;

	for (fnk = 0, fni = fnstart; fni < fnstop; fni++)
		if (fnpathstr[fni] != ':')
			fnbuf[fnk++] = fnpathstr[fni];
	fnbuf[fnk] = 0;
	return (fnbuf);
}

/**
 * fn_fnd_path - finds this fncmd in the PATH string
 * @info: the info struct
 * @fnpathstr: the PATH string
 * @fncmd: the fncmd to find
 *
 * Return: full fnpath of fncmd if found or NULL
 */
char *fn_fnd_path(fninfopass_t *info, char *fnpathstr, char *fncmd)
{
	int fni = 0, curr_pos = 0;
	char *fnpath;

	if (!fnpathstr)
		return (NULL);
	if ((_fn_strnlen(fncmd) > 2) && fn_degin_with(fncmd, "./"))
	{
		if (fn_is_command(info, fncmd))
			return (fncmd);
	}
	while (1)
	{
		if (!fnpathstr[fni] || fnpathstr[fni] == ':')
		{
			fnpath = fn_duplicate_chars(fnpathstr, curr_pos, fni);
			if (!*fnpath)
				_fn_strncat(fnpath, fncmd);
			else
			{
				_fn_strncat(fnpath, "/");
				_fn_strncat(fnpath, fncmd);
			}
			if (fn_is_command(info, fnpath))
				return (fnpath);
			if (!fnpathstr[fni])
				break;
			curr_pos = fni;
		}
		fni++;
	}
	return (NULL);
}
