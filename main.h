#ifndef _SHELL_MAIN_
#define _SHELL_MAIN_
#define UNUSED(x) (void)(x)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>

/**
 * struct history - An structure for each command readed
 * @str: string
 * @counter: number of imputs
 * @next: Next element
 */

typedef struct history
{
	char *str;
	int counter;
	struct history *next;

} history_t;

/**fixing**/
/**** Estructura con las posibles variables que vamos a usar ****/
/**
 * struct variables - variables
 * @array_tokens: array of tokens(arguments)
  * @buffer: buffer of command
  * @status: to handle exit status
  * @argv: gets arguments at opening of shell
  * @counter: counts commands entered
  * @env: has enviroment
  * @commands: have commands.
  * @history: structure
  * @invert: structure
 */
typedef struct variables
{
	char **array_tokens;
	char *buffer;
	int status;
	char **argv;
	int counter;
	char **env;
	char **commands;
	history_t *history;
	history_t *invert;

} vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

/******Some String operations and manipulation******/
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
ssize_t _puts(char *str);
int _strlen(char *str);
void print_str(char *str, int new_line);
int _write_char(char c);
int print_number(int n);

/*** BUILTINGS PROTOTYPES ****/
void (*check_for_builtins(vars_t *vars))(vars_t *vars);
void new_exit(vars_t *vars);
void _env(vars_t *vars);
void new_setenv(vars_t *vars);
void new_unsetenv(vars_t *vars);
void new_help(vars_t *vars);
void new_cd(vars_t *vars);

/** functions related to tokenizer **/
char **tokenizer(char *buffer, char *delimiter);
unsigned int check_if_match(char c, const char *str);
char **_realloc(char **ptr, size_t *size);
char *new_strtok(char *str, const char *delim);

/** second tokenizer**/
char **tokenize(int token_count, char *line, const char *delimiter);
char **token_interface(char *line, const char *delimiter, int token_count);
int count_token(char *line, const char *delimiter);

/** functions related ask external shell, ask the path**/
void check_for_path(vars_t *vars);

/** function to handle error messages, used to help exit function*/
void _puts_error(char *str);
void prints_error_msg(vars_t *vars, char *msg);
char *integer_converter(unsigned int count);

/** function to help exit builting*/
int _atoi(char *str);

/** functions de help env builting*/
/*this to get enviroment*/
char **make_enviroment(char **env);
void free_env(char **env);

/**New_help functions**/
void new_help_exit(vars_t *vars);
void new_help_help(vars_t *vars);
void new_help_cd(vars_t *vars);
void new_help_env(vars_t *vars);
void new_help_history(vars_t *vars);
void new_help_unalias(vars_t *vars);
void new_help_unset(vars_t *vars);
void new_help_unsetenv(vars_t *vars);
void new_help_setenv(vars_t *vars);
void new_help_alias(vars_t *vars);
void new_help_else(vars_t *vars);

/** FUNCTIONS FOR SETENV AND UNSETENV**/
void new_setenv(vars_t *vars);
void add_key(vars_t *vars);
char *add_value(char *key, char *value);
char **find_key(char **env, char *key);
void setenv_cd(char **args, vars_t *vars);
void chdir_to_env(vars_t *vars, char *str);

/** ask the path **/
void fork_child(vars_t vars);
char *path_finder(vars_t vars, char *command);
int find_env_index(vars_t vars, char *str);
char **tokenize_path(vars_t vars, int index, char *str);
char *search_directories(char **path_tokens, char *command);
char *build_path(char *directory, char *command);

/** More handle error messages**/
void error_printing(char *av, int count, char *command);
void exec_error(char *av, int count, char *tmp_command);
void simple_error(void);
void print_cd_1(vars_t *vars);
void print_cd_2(vars_t *vars);

/**history build function**/
void new_history(vars_t *vars);
void *add_nodeint(history_t **head, char *str);
void free_listint(history_t *head);
ssize_t _puts3(char *str);
void print_message(char *str);
/** handles signals**/

void end_of_file(char *buffer);
unsigned int sig_flag;
#endif /* _SHELL_MAIN_ */
