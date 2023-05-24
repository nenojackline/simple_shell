#include "shell.h"

/**
 * fnclr_info - initializes fninfopass_t struct
 * @info: struct address
 */
void fnclr_info(fninfopass_t *info)
{
	info->fnarg = NULL;
	info->fnargv = NULL;
	info->fnpath = NULL;
	info->fnargc = 0;
}

/**
 * fnset_info - initializes fninfopass_t struct
 * @info: struct address
 * @fnav: argument vector
 */
void fnset_info(fninfopass_t *info, char **fnav)
{
	int fni = 0;

	info->fnfname = fnav[0];
	if (info->fnarg)
	{
		info->fnargv = fn_strntow(info->fnarg, " \t");
		if (!info->fnargv)
		{

			info->fnargv = malloc(sizeof(char *) * 2);
			if (info->fnargv)
			{
				info->fnargv[0] = _fn_strndup(info->fnarg);
				info->fnargv[1] = NULL;
			}
		}
		for (fni = 0; info->fnargv && info->fnargv[fni]; fni++)
			;
		info->fnargc = fni;

		fnReplaceAlias(info);
		fnReplaceVars(info);
	}
}

/**
 * fnfree_info - frees fninfopass_t struct fields
 * @info: struct address
 * @fnall: true if freeing fnall fields
 */
void fnfree_info(fninfopass_t *info, int fnall)
{
	fnffree(info->fnargv);
	info->fnargv = NULL;
	info->fnpath = NULL;
	if (fnall)
	{
		if (!info->fncmd_buf)
			free(info->fnarg);
		if (info->fnenv)
			fnFreeList(&(info->fnenv));
		if (info->fnhistory)
			fnFreeList(&(info->fnhistory));
		if (info->fnalias)
			fnFreeList(&(info->fnalias));
		fnffree(info->environ);
			info->environ = NULL;
		fnbfree((void **)info->fncmd_buf);
		if (info->fnreadfd > 2)
			close(info->fnreadfd);
		_fn_putchar(BUFFER_FLUSH);
	}
}
