#include "shell.h"

/**
 * main - Toggles a shell interperter
 * Return: void
 */
int main(void)
{
	char command[100];
	char *path[] = {NULL};
	char *argv[100];
	char *token;
	int i;
	pid_t pid;

	argv[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");
		if (fgets(command, sizeof(command), stdin) == NULL)
			break;

		command[strcspn(command, "\n")] = 0;
		if (strcmp(command, "exit") == 0)
			break;

		token = strtok(command, " ");
		i = 0;
		while (token != NULL)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, " ");
		}

		argv[i] = NULL;

		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, path) == -1)
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
