#include <stdio.h>
#include <stdlib.h>

/**
 * main - is a function
 * @ac: is the number of items in av
 * @av:  is a NULL terminated array of strings.
 * Return: 0
 */

int main(int ac, char **av)
{
	(void)ac;

	int i = 0;

	for (i = 1; av[i] != NULL; i++)
	{
		printf("%s\n", av[i]);
	}
	printf("\n");
	return (0);
}
