#include "shell.h"

/**
 * fnclr_info - initializes fninfopass_t struct
 * @info: struct address
 */
void fnclr_info(fninfopass_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * fnset_info - initializes fninfopass_t struct
 * @info: struct address
 * @av: argument vector
 */
void fnset_info(fninfopass_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = fn_strntow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _fn_strndup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		fnReplaceAlias(info);
		fnReplaceVars(info);
	}
}

/**
 * fnfree_info - frees fninfopass_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void fnfree_info(fninfopass_t *info, int all)
{
	fnffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			fnFreeList(&(info->env));
		if (info->history)
			fnFreeList(&(info->history));
		if (info->alias)
			fnFreeList(&(info->alias));
		fnffree(info->environ);
			info->environ = NULL;
		fnbfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_fn_putchar(BUF_FLUSH);
	}
}
