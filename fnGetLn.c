#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @fnbuf: address of buffer
 * @fnlen: address of fnlen var
 *
 * Return: bytes read
 */
ssize_t input_buf(fninfopass_t *info, char **fnbuf, size_t *fnlen)
{
	ssize_t fnm = 0;
	size_t fnlen_p = 0;

	if (!*fnlen) /* if nothing left in the buffer, fill it */
	{
		/*fnbfree((void **)info->fncmd_buf);*/
		free(*fnbuf);
		*fnbuf = NULL;
		signal(SIGINT, fnsigintHandler);
#if FNUSE_GETLN
		fnm = getline(fnbuf, &fnlen_p, stdin);
#else
		fnm = _fngetline(info, fnbuf, &fnlen_p);
#endif
		if (fnm > 0)
		{
			if ((*fnbuf)[fnm - 1] == '\n')
			{
				(*fnbuf)[fnm - 1] = '\0'; /* remove trailing newline */
				fnm--;
			}
			info->fnlinecount_flag = 1;
			fndelcomments(*fnbuf);
			fnbuildHistoryList(info, *fnbuf, info->fnhistcount++);
			/* if (_fn_strngchr(*fnbuf, ';')) is this a command chain? */
			{
				*fnlen = fnm;
				info->fncmd_buf = fnbuf;
			}
		}
	}
	return (fnm);
}

/**
 * fngetinput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t fngetinput(fninfopass_t *info)
{
	static char *fnbuf; /* the ';' command chain buffer */
	static size_t fni, fnj, fnlen;
	ssize_t fnm = 0;
	char **fnbuf_p = &(info->fnarg), *fnp;

	_fn_putchar(BUFFER_FLUSH);
	fnm = input_buf(info, &fnbuf, &fnlen);
	if (fnm == -1) /* EOF */
		return (-1);
	if (fnlen)	/* we have commands left in the chain buffer */
	{
		fnj = fni; /* init new iterator to current fnbuf position */
		fnp = fnbuf + fni; /* get pointer for return */

		fnCheckChain(info, fnbuf, &fnj, fni, fnlen);
		while (fnj < fnlen) /* iterate to semicolon or end */
		{
			if (fnIsChain(info, fnbuf, &fnj))
				break;
			fnj++;
		}

		fni = fnj + 1; /* increment past nulled ';'' */
		if (fni >= fnlen) /* reached end of buffer? */
		{
			fni = fnlen = 0; /* reset position and length */
			info->fncmd_buf_type = FN_COMD_NORM;
		}

		*fnbuf_p = fnp; /* pass back pointer to current command position */
		return (_fn_strnlen(fnp)); /* return length of current command */
	}

	*fnbuf_p = fnbuf; /* else not a chain, pass back buffer from _fngetline() */
	return (fnm); /* return length of buffer from _fngetline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @fnbuf: buffer
 * @fni: size
 *
 * Return: fnm
 */
ssize_t read_buf(fninfopass_t *info, char *fnbuf, size_t *fni)
{
	ssize_t fnm = 0;

	if (*fni)
		return (0);
	fnm = read(info->fnreadfd, fnbuf, R_BUFFER_SIZE);
	if (fnm >= 0)
		*fni = fnm;
	return (fnm);
}

/**
 * _fngetline - gets the fnnext line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: fns
 */
int _fngetline(fninfopass_t *info, char **ptr, size_t *length)
{
	static char fnbuf[R_BUFFER_SIZE];
	static size_t fni, fnlen;
	size_t fnk;
	ssize_t fnm = 0, fns = 0;
	char *fnp = NULL, *fnnew_p = NULL, *fnc;

	fnp = *ptr;
	if (fnp && length)
		fns = *length;
	if (fni == fnlen)
		fni = fnlen = 0;

	fnm = read_buf(info, fnbuf, &fnlen);
	if (fnm == -1 || (fnm == 0 && fnlen == 0))
		return (-1);

	fnc = _fn_strngchr(fnbuf + fni, '\n');
	fnk = fnc ? 1 + (unsigned int)(fnc - fnbuf) : fnlen;
	fnnew_p = _fnrealloc(fnp, fns, fns ? fns + fnk : fnk + 1);
	if (!fnnew_p) /* MALLOC FAILURE! */
		return (fnp ? free(fnp), -1 : -1);

	if (fns)
		_fn_strngcat(fnnew_p, fnbuf + fni, fnk - fni);
	else
		_fn_strngcpy(fnnew_p, fnbuf + fni, fnk - fni + 1);

	fns += fnk - fni;
	fni = fnk;
	fnp = fnnew_p;

	if (length)
		*length = fns;
	*ptr = fnp;
	return (fns);
}

/**
 * fnsigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void fnsigintHandler(__attribute__((unused))int sig_num)
{
	_fn_puts("\n");
	_fn_puts("$ ");
	_fn_putchar(BUFFER_FLUSH);
}
