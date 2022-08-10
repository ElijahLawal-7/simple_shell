#include "main.h"
/**
 * new_help - help builtin command
 * @vars: if command matches a builtin name, text file is sent to stdout
 * Return: 0 if sucess
 */

void new_help(vars_t *vars)
{
	char *file;
	int fd, r;
	char *s;

	if (vars->array_tokens[1] == NULL)
	{
		file = "/home/shell_test/shelltestenviroment/helpfiles/help";
		fd = open(file, O_RDWR);

		s = malloc(300);
		if (s == NULL)
		{
			_puts_error("Fatal Error");
			return;
		}
		while ((r = read(fd, s, 300)) > 0)
		{
			r = write(1, s, r);
			print_message("\n");
			if (r == -1)
			{
				_puts_error("Fatal Error");
				return;
			}
		}
		free(s);
		fd = close(fd);
		return;
	}
	else
		new_help_help(vars);
}

/**
 * new_help_help - help builtin command help
 * @vars: if command matches a builtin name, text file is sent to stdout
 * Return: 0 if sucess
 */
void new_help_help(vars_t *vars)
{
	char *file;
	int fd, r;
	char *s;

	if (_strcmpr(vars->array_tokens[1], "help") == 0)
	{
		file = "/home/shell_test/shelltestenviroment/helpfiles/help_help";
		fd = open(file, O_RDWR);

		s = malloc(300);
		if (s == NULL)
		{
			_puts_error("Fatal Error");
			return;
		}
		while ((r = read(fd, s, 300)) > 0)
		{
			r = write(1, s, r);
			print_message("\n");
			if (r == -1)
			{
				_puts_error("Fatal Error");
				return;
			}
		}
		free(s);
		fd = close(fd);
	}
	else
		new_help_exit(vars);
}

/**
 * new_help_exit - help builtin command exit
 * @vars: if command matches a builtin name, text file is sent to stdout
 * Return: 0 if sucess
 */
void new_help_exit(vars_t *vars)
{
	char *file;
	int fd, r;
	char *s;

	if (_strcmpr(vars->array_tokens[1], "exit") == 0)
	{
		file = "/home/shell_test/shelltestenviroment/helpfiles/exit";
		fd = open(file, O_RDWR);

		s = malloc(300);
		if (s == NULL)
		{
			_puts_error("Fatal Error");
			return;
		}
		while ((r = read(fd, s, 300)) > 0)
		{
			r = write(1, s, r);
			print_message("\n");
			if (r == -1)
			{
				_puts_error("Fatal Error");
				return;
			}
		}
		free(s);
		fd = close(fd);
	}

	else
		new_help_cd(vars);
}
/**
 * new_help_cd - help builtin command cd
 * @vars: if command matches a builtin name, text file is sent to stdout
 * Return: 0 if sucess
 */
void new_help_cd(vars_t *vars)
{
	char *file;
	int fd, r;
	char *s;

	if (_strcmpr(vars->array_tokens[1], "cd") == 0)
	{
		file = "/home/shell_test/shelltestenviroment/helpfiles/cd";
		fd = open(file, O_RDWR);

		s = malloc(300);
		if (s == NULL)
		{
			_puts_error("Fatal Error");
			return;
		}
		while ((r = read(fd, s, 300)) > 0)
		{
			r = write(1, s, r);
			print_message("\n");
			if (r == -1)
			{
				_puts_error("Fatal Error");
				return;
			}
		}
		free(s);
		fd = close(fd);
	}

	else
		new_help_env(vars);
}
/**
 * new_help_env - help builtin command env
 * @vars: if command matches a builtin name, text file is sent to stdout
 * Return: 0 if sucess
 */
void new_help_env(vars_t *vars)
{
	char *file;
	int fd, r;
	char *s;

	if (_strcmpr(vars->array_tokens[1], "env") == 0)
	{
		file = "/home/shell_test/shelltestenviroment/helpfiles/env";
		fd = open(file, O_RDWR);

		s = malloc(300);
		if (s == NULL)
		{
			_puts_error("Fatal Error");
			return;
		}
		while ((r = read(fd, s, 300)) > 0)
		{
			r = write(1, s, r);
			print_message("\n");
			if (r == -1)
			{
				_puts_error("Fatal Error");
				return;
			}
		}
		free(s);
		fd = close(fd);
	}
	else
		new_help_history(vars);
}
