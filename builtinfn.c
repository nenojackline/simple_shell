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
	int fnexit_check;

	if (info->fnargv[1])  /* If there is an exit arguement */
	{
		fnexit_check = _fnerratoi(info->fnargv[1]);
		if (fnexit_check == -1)
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
	char *sp, *fndir, fnbuffer[1024];
	int chdir_ret;

	sp = getcwd(fnbuffer, 1024);
	if (!sp)
		_fn_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->fnargv[1])
	{
		fndir = _fngetenv(info, "HOME=");
		if (!fndir)
			chdir_ret = /* TODO: what should this be? */
				chdir((fndir = _fngetenv(info, "PWD=")) ? fndir : "/");
		else
			chdir_ret = chdir(fndir);
	}
	else if (_fn_strncmp(info->fnargv[1], "-") == 0)
	{
		if (!_fngetenv(info, "OLDPWD="))
		{
			_fn_puts(sp);
			_fn_putchar('\n');
			return (1);
		}
		_fn_puts(_fngetenv(info, "OLDPWD=")), _fn_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((fndir = _fngetenv(info, "OLDPWD=")) ? fndir : "/");
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
		_fn_setenv(info, "PWD", getcwd(fnbuffer, 1024));
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
	char **fnarg_array;

	fnarg_array = info->fnargv;
	_fn_puts("help call works. Function not yet implemented \n");
	if (0)
		_fn_puts(*fnarg_array); /* temp att_unused workaround */
	return (0);
}
