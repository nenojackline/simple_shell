#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for fncnvrtnumber() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststring - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} lst_t;

/**
 *struct fnpassinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct fnpassinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	lst_t *env;
	lst_t *history;
	lst_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
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

/* path.c */
int fn_is_command(fninfopass_t *, char *);
char *fn_duplicate_chars(char *, int, int);
char *fn_fnd_path(fninfopass_t *, char *, char *);

/* fn_lpshs.c */
int fn_lpshs(char **);

/* err_string_functions.c */
void _fneputs(char *);
int _fneputschar(char);
int _fneputsfd(char c, int fd);
int _fn_putsfd(char *str, int fd);

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

/* env.c module */
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
