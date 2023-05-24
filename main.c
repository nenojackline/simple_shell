#include "shell.h"

/**
 * main - entry point
 * @fnac: fnarg count
 * @fnav: fnarg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int fnac, char **fnav)
{
	fninfopass_t info[] = { INFO_INIT };
	int fnfd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fnfd)
		: "r" (fnfd));

	if (fnac == 2)
	{
		fnfd = open(fnav[1], O_RDONLY);
		if (fnfd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_fneputs(fnav[0]);
				_fneputs(": 0: Can't open ");
				_fneputs(fnav[1]);
				_fneputschar('\n');
				_fneputschar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->fnreadfd = fnfd;
	}
	fnpopulateEnvList(info);
	fnread_history(info);
	fnhsh(info, fnav);
	return (EXIT_SUCCESS);
}
