#include "shell.h"

/**
 * _fnexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit fnstatus
 *         (0) if info.fnargv[0] != "exit"
 */
int _fnexit(fninfopass_t *info)
{
	int exitcheck;

	if (info->fnargv[1])  /* If there is an exit arguement */
	{
		exitcheck = _fnerratoi(info->fnargv[1]);
		if (exitcheck == -1)
		{
			info->fnstatus = 2;
			fnprnterr(info, "Illegal number: ");
			_fneputs(info->fnargv[1]);
			_fneputschar('\n');
			return (1);
		}
		info->fnerr_num = _fnerratoi(info->fnargv[1]);
		return (-2);
	}
	info->fnerr_num = -1;
	return (-2);
}

/**
 * _fncd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _fncd(fninfopass_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_fn_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->fnargv[1])
	{
		dir = _fngetenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _fngetenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_fn_strncmp(info->fnargv[1], "-") == 0)
	{
		if (!_fngetenv(info, "OLDPWD="))
		{
			_fn_puts(s);
			_fn_putchar('\n');
			return (1);
		}
		_fn_puts(_fngetenv(info, "OLDPWD=")), _fn_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _fngetenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->fnargv[1]);
	if (chdir_ret == -1)
	{
		fnprnterr(info, "can't cd to ");
		_fneputs(info->fnargv[1]), _fneputschar('\n');
	}
	else
	{
		_fn_setenv(info, "OLDPWD", _fngetenv(info, "PWD="));
		_fn_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _fnhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _fnhelp(fninfopass_t *info)
{
	char **arg_array;

	arg_array = info->fnargv;
	_fn_puts("help call works. Function not yet implemented \n");
	if (0)
		_fn_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
