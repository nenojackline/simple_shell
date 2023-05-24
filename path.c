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
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *fn_duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * fn_fnd_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full fnpath of cmd if found or NULL
 */
char *fn_fnd_path(fninfopass_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *fnpath;

	if (!pathstr)
		return (NULL);
	if ((_fn_strnlen(cmd) > 2) && fn_degin_with(cmd, "./"))
	{
		if (fn_is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			fnpath = fn_duplicate_chars(pathstr, curr_pos, i);
			if (!*fnpath)
				_fn_strncat(fnpath, cmd);
			else
			{
				_fn_strncat(fnpath, "/");
				_fn_strncat(fnpath, cmd);
			}
			if (fn_is_command(info, fnpath))
				return (fnpath);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
