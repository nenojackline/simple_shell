#include "shell.h"

/**
 * fnget_history_file - gets the fnhistory file
 * @info: parameter struct
 *
 * Return: allocated string containg fnhistory file
 */

char *fnget_history_file(fninfopass_t *info)
{
	char *buf, *dir;

	dir = _fngetenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_fn_strnlen(dir) + _fn_strnlen(BCKPFILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_fn_strncopy(buf, dir);
	_fn_strncat(buf, "/");
	_fn_strncat(buf, BCKPFILE);
	return (buf);
}

/**
 * fnwrite_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int fnwrite_history(fninfopass_t *info)
{
	ssize_t fd;
	char *filename = fnget_history_file(info);
	lst_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->fnhistory; node; node = node->fnnext)
	{
		_fn_putsfd(node->fnstr, fd);
		_fneputsfd('\n', fd);
	}
	_fneputsfd(BUFFER_FLUSH, fd);
	close(fd);
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
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = fnget_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			fnbuildHistoryList(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		fnbuildHistoryList(info, buf + last, linecount++);
	free(buf);
	info->fnhistcount = linecount;
	while (info->fnhistcount-- >= HISTMAX)
		fnDeleteNodeAtIndex(&(info->fnhistory), 0);
	fnRenumberHistory(info);
	return (info->fnhistcount);
}

/**
 * fnbuildHistoryList - adds entry to a fnhistory linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the fnhistory linecount, fnhistcount
 *
 * Return: Always 0
 */
int fnbuildHistoryList(fninfopass_t *info, char *buf, int linecount)
{
	lst_t *node = NULL;

	if (info->fnhistory)
		node = info->fnhistory;
	fnAddNodeEnd(&node, buf, linecount);

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
	int i = 0;

	while (node)
	{
		node->fnnum = i++;
		node = node->fnnext;
	}
	return (info->fnhistcount = i);
}
