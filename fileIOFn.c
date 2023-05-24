#include "shell.h"

/**
 * fnget_history_file - gets the fnhistory file
 * @info: parameter struct
 *
 * Return: allocated string containg fnhistory file
 */

char *fnget_history_file(fninfopass_t *info)
{
	char *fnbuf, *fndir;

	fndir = _fngetenv(info, "HOME=");
	if (!fndir)
		return (NULL);
fnbuf = malloc(sizeof(char) * (_fn_strnlen(fndir) +
	_fn_strnlen(BCKPFILE) + 2));
	if (!fnbuf)
		return (NULL);
	fnbuf[0] = 0;
	_fn_strncopy(fnbuf, fndir);
	_fn_strncat(fnbuf, "/");
	_fn_strncat(fnbuf, BCKPFILE);
	return (fnbuf);
}

/**
 * fnwrite_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int fnwrite_history(fninfopass_t *info)
{
	ssize_t fnfd;
	char *filename = fnget_history_file(info);
	lst_t *node = NULL;

	if (!filename)
		return (-1);

	fnfd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fnfd == -1)
		return (-1);
	for (node = info->fnhistory; node; node = node->fnnext)
	{
		_fn_putsfd(node->fnstr, fnfd);
		_fneputsfd('\n', fnfd);
	}
	_fneputsfd(BUFFER_FLUSH, fnfd);
	close(fnfd);
	return (1);
}

/**
 * fnread_history - reads fnhistory from file
 * @info: the parameter struct
 *
 * Return: fnhistcount on success, 0 otherwise
 */
int fnread_history(fninfopass_t *info)
{
	int fni, fnlast = 0, fnlinecount = 0;
	ssize_t fnfd, fnrdlen, fnfsize = 0;
	struct stat st;
	char *fnbuf = NULL, *filename = fnget_history_file(info);

	if (!filename)
		return (0);

	fnfd = open(filename, O_RDONLY);
	free(filename);
	if (fnfd == -1)
		return (0);
	if (!fstat(fnfd, &st))
		fnfsize = st.st_size;
	if (fnfsize < 2)
		return (0);
	fnbuf = malloc(sizeof(char) * (fnfsize + 1));
	if (!fnbuf)
		return (0);
	fnrdlen = read(fnfd, fnbuf, fnfsize);
	fnbuf[fnfsize] = 0;
	if (fnrdlen <= 0)
		return (free(fnbuf), 0);
	close(fnfd);
	for (fni = 0; fni < fnfsize; fni++)
		if (fnbuf[fni] == '\n')
		{
			fnbuf[fni] = 0;
			fnbuildHistoryList(info, fnbuf + fnlast, fnlinecount++);
			fnlast = fni + 1;
		}
	if (fnlast != fni)
		fnbuildHistoryList(info, fnbuf + fnlast, fnlinecount++);
	free(fnbuf);
	info->fnhistcount = fnlinecount;
	while (info->fnhistcount-- >= HISTMAX)
		fnDeleteNodeAtIndex(&(info->fnhistory), 0);
	fnRenumberHistory(info);
	return (info->fnhistcount);
}

/**
 * fnbuildHistoryList - adds entry to a fnhistory linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @fnbuf: buffer
 * @fnlinecount: the fnhistory fnlinecount, fnhistcount
 *
 * Return: Always 0
 */
int fnbuildHistoryList(fninfopass_t *info, char *fnbuf, int fnlinecount)
{
	lst_t *node = NULL;

	if (info->fnhistory)
		node = info->fnhistory;
	fnAddNodeEnd(&node, fnbuf, fnlinecount);

	if (!info->fnhistory)
		info->fnhistory = node;
	return (0);
}

/**
 * fnRenumberHistory - renumbers the fnhistory linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new fnhistcount
 */
int fnRenumberHistory(fninfopass_t *info)
{
	lst_t *node = info->fnhistory;
	int fni = 0;

	while (node)
	{
		node->fnnum = fni++;
		node = node->fnnext;
	}
	return (info->fnhistcount = fni);
}
