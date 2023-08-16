#include "shell.h"

/**
 * main - Toggles a shell interperter
 * Return: void
 */
int main(void)
{
	char command[100];
	char *path[] = {NULL};
	char *argv[2];
	pid_t pid;

	argv[1] = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			break;
		}

		command[strcspn(command, "\n")] = 0;
		if (strcmp(command, "exit") == 0)
		{
			break;
		}

		argv[0] = command;

		pid = fork();
		if (pid == 0)
		{
			if (execve(command, argv, path) == -1)
			{
				fprintf(stderr, "./shell: No such file or directory\n");
				return (1);
			}
		}
		else if (pid < 0)
			fprintf(stderr, "Error: Fork failed\n");
		else
			wait(NULL);
	}

	return (0);
}
