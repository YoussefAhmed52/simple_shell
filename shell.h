#ifndef SHELL_H
#define SHELL_H

#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>





/* for write/read buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for chaining command */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for number_convert function */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


/* if using system get_line() will be 1 */
#define USE_STRTOK 0
#define USE_GETLINE 0


#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"


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
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from get_line containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environment
 *@environ: custom modified copy of environment from LL env
 *@history: the history node
 *@alias: the alias node
 *@environment_changed: on if environment was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buffer, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int environment_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built - contains a built in string and related function
 *@type: the built in command flag
 *@func: the function
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} built_in_table;


/* _hshell.c */
void cmd_find(info_t *);
void cmd_fork(info_t *);
int _hsh(info_t *, char **);
int find_built_in(info_t *);


/* paths.c */
char *chars_dup(char *, int, int);
char *path_find(info_t *, char *, char *);
int cmd_is(info_t *, char *);


/* loophshell.c */
int loophsh(char **);

/* error_string_functions.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);


/* strings_functions.c */
char *starts_with_haystack(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);


/* strings_functions2.c */
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);


/* strings_functions3.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);



/* strings_functions4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memorys_functions */
void f_free(char **);
void *_re_alloc(void *, unsigned int, unsigned int);
char *_memory_set(char *, char, unsigned int);


/* memorys_functions2.c */
int b_free(void **);

/* extra_functions.c */
int _is_alpha(int);
int interactive_mode(info_t *);
int _atoi(char *);
int is_delimeter(char, char *);



/* extra_functions2.c */
char *number_convert(long int, int, int);
int _atoierr(char *);
int dec_print(int, int);
void error_print(info_t *, char *);
void comments_removal(char *);


/* get_line.c module */
void sigint_Handler(int);
int _get_line(info_t *, char **, size_t *);
ssize_t input_get(info_t *);
ssize_t buf_input(info_t *info, char **buf, size_t *len);
ssize_t buf_read(info_t *info, char *buf, size_t *i);




/* built_in_emulators.c */
int _my_exit(info_t *);
int _my_cd(info_t *);
int _my_help(info_t *);

/* built_in_emulators2.c */
int _my_history(info_t *);
int _my_alias(info_t *);
int alias_unset(info_t *info, char *str);
int alias_set(info_t *info, char *str);
int alias_print(list_t *node);



/* infos.c module */
void info_free(info_t *, int);
void info_clear(info_t *);
void info_set(info_t *, char **);



/* environ.c module */
int _my_env(info_t *);
int _my_envset(info_t *);
int _my_unsetenv(info_t *);
int env_list_populate(info_t *);
char *_envget(info_t *, const char *);


/* environ2.c module */
int _unsetenv(info_t *, char *);
int _envset(info_t *, char *, char *);
char **get_environment(info_t *);


/* files_io_functions.c */
int write_history(info_t *info);
int history_read(info_t *info);
int history_list_build(info_t *info, char *buf, int linecount);
int history_renumber(info_t *info);
char *get_history_f(info_t *info);


/* list_string.c module */
int node_at_index_delete(list_t **, unsigned int);
void free_list(list_t **);
list_t *node_add(list_t **, const char *, int);
list_t *node_add_end(list_t **, const char *, int);
size_t print_str_list(const list_t *);


/* list_string2.c module */
size_t list_length(const list_t *);
size_t list_print(const list_t *);
ssize_t get_index_of_node(list_t *, list_t *);
char **convert_list_to_strings(list_t *);
list_t *node_starts_with_prefix(list_t *, char *, char);


/* chains.c */
int string_replace(char **, char *);
int _chain(info_t *, char *, size_t *);
int vars_replace(info_t *);
int alias_replace(info_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);



#endif

