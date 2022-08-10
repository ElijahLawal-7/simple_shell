#include <stdio.h>
#include <unistd.h>

/**
 * main - PPID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;

	my_pid = getpid();
	printf("Hello monemax your pid is: %u\n", my_pid);
	my_pid = getppid();
	printf("Hello monemax your ppid is: %u\n", my_pid);

	return (0);
}
