#include "shell.h"

/**
 * fnhsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int fnhsh(fninfopass_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		fnclr_info(info);
		if (fninteractive(info))
			_fn_puts("$ ");
		_fneputschar(BUFFER_FLUSH);
		r = fngetinput(info);
		if (r != -1)
		{
			fnset_info(info, av);
			builtin_ret = fn_fnd_builtin(info);
			if (builtin_ret == -1)
				fn_fnd_command(info);
		}
		else if (fninteractive(info))
			_fn_putchar('\n');
		fnfree_info(info, 0);
	}
	fnwrite_history(info);
	fnfree_info(info, 1);
	if (!fninteractive(info) && info->fnstatus)
		exit(info->fnstatus);
	if (builtin_ret == -2)
	{
		if (info->fnerr_num == -1)
			exit(info->fnstatus);
		exit(info->fnerr_num);
	}
	return (builtin_ret);
}

/**
 * fn_fnd_builtin - finds a fnbuiltin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if fnbuiltin not found,
 *			0 if fnbuiltin executed successfully,
 *			1 if fnbuiltin found but not successful,
 *			-2 if fnbuiltin signals exit()
 */
int fn_fnd_builtin(fninfopass_t *info)
{
	int i, built_in_ret = -1;
	fn_builtin_t builtintbl[] = {
		{"exit", _fnexit},
		{"fnenv", _fnenv},
		{"help", _fnhelp},
		{"fnhistory", _fnhistory},
		{"setenv", _fnsetenv},
		{"unsetenv", _fnunsetenv},
		{"cd", _fncd},
		{"fnalias", _fnalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_fn_strncmp(info->fnargv[0], builtintbl[i].type) == 0)
		{
			info->fnline_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * fn_fnd_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fn_fnd_command(fninfopass_t *info)
{
	char *fnpath = NULL;
	int i, k;

	info->fnpath = info->fnargv[0];
	if (info->fnlinecount_flag == 1)
	{
		info->fnline_count++;
		info->fnlinecount_flag = 0;
	}
	for (i = 0, k = 0; info->fnarg[i]; i++)
		if (!fnisdelim(info->fnarg[i], " \t\n"))
			k++;
	if (!k)
		return;

	fnpath = fn_fnd_path(info, _fngetenv(info, "PATH="), info->fnargv[0]);
	if (fnpath)
	{
		info->fnpath = fnpath;
		fn_frk_command(info);
	}
	else
	{
		if ((fninteractive(info) || _fngetenv(info, "PATH=")
			|| info->fnargv[0][0] == '/') && fn_is_command(info, info->fnargv[0]))
			fn_frk_command(info);
		else if (*(info->fnarg) != '\n')
		{
			info->fnstatus = 127;
			fnprnterr(info, "not found\n");
		}
	}
}

/**
 * fn_frk_command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fn_frk_command(fninfopass_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->fnpath, info->fnargv, fnget_environ(info)) == -1)
		{
			fnfree_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->fnstatus));
		if (WIFEXITED(info->fnstatus))
		{
			info->fnstatus = WEXITSTATUS(info->fnstatus);
			if (info->fnstatus == 126)
				fnprnterr(info, "Permission denied\n");
		}
	}
}
