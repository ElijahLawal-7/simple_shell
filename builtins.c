#include "main.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{"cd", new_cd},
		{"help", new_help},


		{NULL, NULL}};

	for (i = 0; check[i].f != NULL; i++)
	{
		/** vars->array_tokens esta accediendo a los argumentos para el match */
		if (_strcmpr(vars->array_tokens[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(vars);
	return (check[i].f);
}

/**
 * new_exit - exit program
 * @vars: variables
 * Return: void
 */
void new_exit(vars_t *vars)
{

	int status;
	/**Si exit tiene argumentos, lo manejamos*/
	if (_strcmpr(vars->array_tokens[0], "exit") ==
			0 &&
		vars->array_tokens[1] != NULL)

	{
		/* con esta funcion nos aseguramos que el numero ingresado sea valido*/
		status = _atoi(vars->array_tokens[1]);
		/* manejamos caso de error*/
		if (status == -1)
		{
			vars->status = 2;
			/*imprimira un mensaje de error */
			prints_error_msg(vars, ": Illegal number: ");
			print_message(vars->array_tokens[1]);
			print_message("\n");
			return;
		}
		vars->status = status;
	}
	free(vars->commands);
	free(vars->array_tokens);


	free_env(vars->env);
	free(vars->buffer);
	exit(vars->status);
}

/**
 * _env - prints the current environment
 * @vars: struct of variables
 * Return: void.
 */
void _env(vars_t *vars)
{
	unsigned int i;

	for (i = 0; vars->env[i]; i++)
	{
		_puts(vars->env[i]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * new_setenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;
	/** si los argumentos de setenv son errones imprimimos mensaje de error**/
	if (vars->array_tokens[1] == NULL || vars->array_tokens[2] == NULL)
	{

		prints_error_msg(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->array_tokens[1]);
	if (key == NULL)
	{
		add_key(vars);
	}
	else
	{
		var = add_value(vars->array_tokens[1], vars->array_tokens[2]);
		if (var == NULL)
		{
			prints_error_msg(vars, NULL);
			free(vars->buffer);
			free(vars->array_tokens);
			free(vars->commands);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * new_unsetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;
	unsigned int i, j;

	if (vars->array_tokens[1] == NULL)
	{
		prints_error_msg(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->array_tokens[1]);
	if (key == NULL)
	{
		prints_error_msg(vars, ": No variable to unset");
		return;
	}
	for (i = 0; vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * i);
	if (newenv == NULL)
	{
		prints_error_msg(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (i = 0; vars->env[i] != *key; i++)
		newenv[i] = vars->env[i];
	for (j = i + 1; vars->env[j] != NULL; j++, i++)
		newenv[i] = vars->env[j];
	newenv[i] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}
