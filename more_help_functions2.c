#include "main.h"

/**
 * new_help_alias - help builtin command alias
 * @vars: if command matches a builtin name, text file is sent to stdout
 * Return: 0 if sucess
 */
void new_help_alias(vars_t *vars)

{
	char *file;
	int fd, r;
	char *s;

	if (_strcmpr(vars->array_tokens[1], "alias") == 0)
	{
		file = "/home/shell_test/shelltestenviroment/helpfiles/alias";
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
		new_help_else(vars);
}
/**
 * new_help_else -error message if not command found
 * @vars: if command matches a builtin name, text file is sent to stdout
 * Return: 0 if sucess
 */

void new_help_else(vars_t *vars)
{

	prints_error_msg(vars, ": no help topics match: `");
	_puts_error(vars->array_tokens[1]);

	_puts_error("'.  Try `help help' or `man -k ");
	_puts_error(vars->array_tokens[1]);
	_puts_error("' or `info ");
	_puts_error(vars->array_tokens[1]);
	_puts_error("'.");

	_puts_error("\n");
}
