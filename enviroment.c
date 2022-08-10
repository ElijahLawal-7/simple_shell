#include "main.h"

/**
 * make_enviroment - make the shell environment from the environment.
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **make_enviroment(char **env)
{
char **newenviroment = NULL;

size_t i;

	for (i = 0; env[i] != NULL; i++)
		;
	newenviroment = malloc(sizeof(char *) * (i + 1));
	if (newenviroment == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; env[i] != NULL; i++)
		newenviroment[i] = _strdup(env[i]);
	newenviroment[i] = NULL;
	return (newenviroment);
}

/**
 * free_env - free the shell's environment
 * @env: shell's environment
 *
 * Return: void
 */
void free_env(char **env)
{
	unsigned int i;

	for (i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env);
}

/**
 * chdir_to_env - go to the directory that points the adress of the
 *                the environment variable.
 * @vars: vars variable of struct vars_t
 * @str: name of env var to find.
 * Return: always return void.
 */
void chdir_to_env(vars_t *vars, char *str)
{
	int len, index;

	len = _strlen(str);
	index = find_env_index(*vars, str);
	chdir((vars->env[index]) + len + 1);
}
