#include "main.h"

/**
 * fork_child - Creates a child in  order to execute another program.
 * @vars: A structure cointaining a array of pointers and a string.
 */
void fork_child(vars_t vars)
{
	pid_t id;
	int status, check;
	struct stat buf;
	char *tmp_command, *command;

	id = fork();
	if (id != 0)
		wait(&status);
	else
	{
		tmp_command = vars.array_tokens[0];
		command = path_finder(vars, vars.array_tokens[0]);
		if (command == NULL)
		{
			/* Looking for file in current directory */
			check = stat(tmp_command, &buf);
			if (check == -1)
			{
				error_printing(vars.argv[0], vars.counter, tmp_command);
				print_str(": not found", 0);

				exit(100);
			}
			/* file exist in cwd or has full path */
			command = tmp_command;
		}
		vars.array_tokens[0] = command;
		if (vars.array_tokens[0] != NULL)
		{
			if (execve(vars.array_tokens[0], vars.array_tokens, vars.env) == -1)
				exec_error(vars.argv[0], vars.counter, tmp_command);
		}
	}
}

/**
 * path_finder - Acts as an interface for functions that will be able
 * to find the full path of a program.
 * @command: A common command such as ls, echo, pwd, etc..
 * Return: On success a string with the full path of the program.
 * @vars: structure with variables.
 * oterwise returns NULL.
 */
char *path_finder(vars_t vars, char *command)
{
	char *str = "PATH";
	char *constructed;
	char **path_tokens;
	int index, i;
	char *directory;

	index = find_env_index(vars, str);
	path_tokens = tokenize_path(vars, index, str);
	if (path_tokens == NULL)
		return (NULL);

	directory = search_directories(path_tokens, command);
	if (directory == NULL)
	{
		for (i = 0; path_tokens[i] != NULL; i++)
			free(path_tokens[i]);
		free(path_tokens);
		return (NULL);
	}
	constructed = build_path(directory, command);
	if (constructed == NULL)
	{
		for (i = 0; path_tokens[i] != NULL; i++)
			free(path_tokens[i]);
		free(path_tokens);
		return (NULL);
	}
	for (i = 0; path_tokens[i] != NULL; i++)
		free(path_tokens[i]);
	free(path_tokens);
	return (constructed);
}

/**
 * find_env_index - Finds the index of an environmental variable.
 * @vars: structure with variables will be used
 * @str: Environmental variable that needs to be found.
 * Return: Upon success returns the inde of the environmental variale
 * otherwise returns -1.
 */
int find_env_index(vars_t vars, char *str)
{
	int i, len, j;

	len = _strlen(str);
	for (i = 0; vars.env[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (vars.env[i][j] != str[j])
				break;
		}
		if (j == len && vars.env[i][j] == '=')
			return (i);
	}
	return (-1);
}

/**
 * tokenize_path - Separates a string of path as an array of
 * strings containing the path directories.
 * @vars: structure with variables will be used
 * @index: index of the path in the environment variables.
 * @str: string to separate and tokenize
 * Return: On success a NLL terminated array of string.
 * otherwise returns NULL.
 */
char **tokenize_path(vars_t vars, int index, char *str)
{
	char *env_var;
	int token_count = 0, len;
	char **path_tokens;
	const char *delim = ":\n";

	len = _strlen(str);

	env_var = vars.env[index] + (len + 1);
	path_tokens = token_interface(env_var, delim, token_count);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}

/**
 * search_directories - Looks through directories stored in path_tokens
 * for a specific file aka command.
 * @path_tokens: A pointer to array of strings containings de paths
 * contained in the PATH environment variable.
 * @command: Represents a command. i.e. ls, /bin/ls, pwd, etc.
 *
 * Return: On success a string with the directory containing the
 * command file. Otherwise NULL.
 */
char *search_directories(char **path_tokens, char *command)
{
	int i, s;
	char *cwd, *buf;
	size_t size;
	struct stat stat_buf;

	buf = NULL;
	size = 0;
	cwd = getcwd(buf, size);
	if (cwd == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (i = 0; path_tokens[i] != NULL; i++)
	{
		s = chdir(path_tokens[i]);
		if (s == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		s = stat(command, &stat_buf);
		if (s == 0)
		{
			chdir(cwd);
			free(cwd);
			return (path_tokens[i]);
		}
	}
	chdir(cwd);
	free(cwd);
	return (NULL);
}
