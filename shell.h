#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* for read/write buffers */
#define R_BUFFER_SIZE 1024
#define W_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define FN_COMD_NORM	0
#define FN_COMD_OR		1
#define FN_COMD_AND		2
#define FN_COMD_CHAIN	3

/* for fncnvrtnumber() */
#define CVNT_LWCASE	1
#define CVNT_UNSD	2

/* 1 if using system getline() */
#define FNUSE_GETLN 0
#define FNUSE_STRTOK 0

#define BCKPFILE	".simple_shell_history"
#define HISTMAX	4096

extern char **fnenviron;


/**
 * struct liststring - singly linked list
 * @fnnum: the number field
 * @fnstr: a string
 * @fnnext: points to the fnnext node
 */
typedef struct liststring
{
	int fnnum;
	char *fnstr;
	struct liststring *fnnext;
} lst_t;

/**
 *struct fnpassinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@fnarg: a string generated from getline containing arguements
 *@fnargv: an array of strings generated from fnarg
 *@fnpath: a string fnpath for the current command
 *@fnargc: the argument count
 *@fnline_count: the error count
 *@fnerr_num: the error code for exit()s
 *@fnlinecount_flag: if on count this line of input
 *@fnfname: the program filename
 *@fnenv: linked list local copy of fnenviron
 *@fnenviron: custom modified copy of fnenviron from LL fnenv
 *@fnhistory: the fnhistory node
 *@fnalias: the fnalias node
 *@fnenv_changed: on if fnenviron was changed
 *@fnstatus: the return fnstatus of the last exec'd command
 *@fncmd_buf: address of pointer to fncmd_buf, on if chaining
 *@fncmd_buf_type: CMD_type ||, &&, ;
 *@fnreadfd: the fd from which to read line input
 *@fnhistcount: the fnhistory line number count
 */
typedef struct fnpassinfo
{
	char *fnarg;
	char **fnargv;
	char *fnpath;
	int fnargc;
	unsigned int fnline_count;
	int fnerr_num;
	int fnlinecount_flag;
	char *fnfname;
	lst_t *fnenv;
	lst_t *fnhistory;
	lst_t *fnalias;
	char **fnenviron;
	int fnenv_changed;
	int fnstatus;

	char **fncmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int fncmd_buf_type; /* CMD_type ||, &&, ; */
	int fnreadfd;
	int fnhistcount;
} fninfopass_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct fnbuiltin - contains a fnbuiltin string and related function
 *@type: the fnbuiltin command flag
 *@func: the function
 */
typedef struct fnbuiltin
{
	char *type;
	int (*func)(fninfopass_t *);
} fn_builtin_t;


/* fnhsh.c */
int fnhsh(fninfopass_t *, char **);
int fn_fnd_builtin(fninfopass_t *);
void fn_fnd_command(fninfopass_t *);
void fn_frk_command(fninfopass_t *);

/* fnpath.c */
int fn_is_command(fninfopass_t *, char *);
char *fn_duplicate_chars(char *, int, int);
char *fn_fnd_path(fninfopass_t *, char *, char *);

/* fn_lpshs.c */
int fn_lpshs(char **);

/* err_string_functions.c */
void _fneputs(char *);
int _fneputschar(char);
int _fneputsfd(char c, int fd);
int _fn_putsfd(char *fnstr, int fd);

/* string_functions.c */
int _fn_strnlen(char *);
int _fn_strncmp(char *, char *);
char *fn_degin_with(const char *, const char *);
char *_fn_strncat(char *, char *);

/* string_functions2.c */
char *_fn_strncopy(char *, char *);
char *_fn_strndup(const char *);
void _fn_puts(char *);
int _fn_putchar(char);

/* string_functions3.c */
char *_fn_strngcpy(char *, char *, int);
char *_fn_strngcat(char *, char *, int);
char *_fn_strngchr(char *, char);

/* string_functions4.c */
char **fn_strntow(char *, char *);
char **fn_strntow2(char *, char);

/* memory_functions */
char *_fn_memryset(char *, char, unsigned int);
void fnffree(char **);
void *_fnrealloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int fnbfree(void **);

/* more_functions.c */
int fninteractive(fninfopass_t *);
int fnisdelim(char, char *);
int _fnis_alpha(int);
int _fnatoi(char *);

/* more_functions2.c */
int _fnerratoi(char *);
void fnprnterr(fninfopass_t *, char *);
int fnprntd(int, int);
char *fncnvrtnumber(long int, int, int);
void fndelcomments(char *);

/* builtin_emulators.c */
int _fnexit(fninfopass_t *);
int _fncd(fninfopass_t *);
int _fnhelp(fninfopass_t *);

/* builtin_emulators2.c */
int _fnhistory(fninfopass_t *);
int _fnalias(fninfopass_t *);

/* getline.c module */
ssize_t fngetinput(fninfopass_t *);
int _fngetline(fninfopass_t *, char **, size_t *);
void fnsigintHandler(int);

/* info.c module */
void fnclr_info(fninfopass_t *);
void fnset_info(fninfopass_t *, char **);
void fnfree_info(fninfopass_t *, int);

/* fnenv.c module */
char *_fngetenv(fninfopass_t *, const char *);
int _fnenv(fninfopass_t *);
int _fnsetenv(fninfopass_t *);
int _fnunsetenv(fninfopass_t *);
int fnpopulateEnvList(fninfopass_t *);

/* env2.c module */
char **fnget_environ(fninfopass_t *);
int _fn_unsetenv(fninfopass_t *, char *);
int _fn_setenv(fninfopass_t *, char *, char *);

/* file_io_functions.c */
char *fnget_history_file(fninfopass_t *info);
int fnwrite_history(fninfopass_t *info);
int fnread_history(fninfopass_t *info);
int fnbuildHistoryList(fninfopass_t *info, char *buf, int linecount);
int fnRenumberHistory(fninfopass_t *info);

/* liststring.c module */
lst_t *fnAddNode(lst_t **, const char *, int);
lst_t *fnAddNodeEnd(lst_t **, const char *, int);
size_t fnPrintListStr(const lst_t *);
int fnDeleteNodeAtIndex(lst_t **, unsigned int);
void fnFreeList(lst_t **);

/* liststr2.c module */
size_t fnListLen(const lst_t *);
char **fnListToStrgs(lst_t *);
size_t fnPrintLists(const lst_t *);
lst_t *fnNodeStartsWith(lst_t *, char *, char);
ssize_t fnGetNodeIndex(lst_t *, lst_t *);

/* chain.c */
int fnIsChain(fninfopass_t *, char *, size_t *);
void fnCheckChain(fninfopass_t *, char *, size_t *, size_t, size_t);
int fnReplaceAlias(fninfopass_t *);
int fnReplaceVars(fninfopass_t *);
int fnReplaceString(char **, char *);

#endif
