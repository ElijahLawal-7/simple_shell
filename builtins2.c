#include "main.h"
/**
 * new_cd - Changes the current working directory .
 * if no parameter is passed it will change directory to HOME.
 * @vars: A string representing the input from the user.
 */
void new_cd(vars_t *vars)
{
	int index;

	if (vars->array_tokens[1] == NULL)
	{
		index = find_env_index(*vars, "HOME");
		chdir((vars->env[index]) + 5);
	}
	else if (_strcmpr(vars->array_tokens[1], "-") == 0)
		print_str(vars->array_tokens[1], 0);
	else
		chdir(vars->array_tokens[1]);
}
