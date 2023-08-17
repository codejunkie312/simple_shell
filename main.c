#include "shell.h"

/**
 * main - Toggles a shell interperter
 * Return: void
 */
int main(void)
{
	char command[100];
	char *argv[100];
	char *token, *full_path;
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
		else if (strcmp(command, "env") == 0)
		{
			print_env();
			break;
		}
		
		token = strtok(command, " ");
		i = 0;
		while (token != NULL)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, " ");
		}

		argv[i] = NULL;
		full_path = find_path(argv[0]);

		if (full_path == NULL)
		{
			fprintf(stderr, "./hsh: No such file or directory\n");
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			if (execve(full_path, argv, NULL) == -1)
			{
				fprintf(stderr, "./hsh: Execution failed\n");
				free(full_path);
				return (1);
			}
		}
		else if (pid < 0)
			fprintf(stderr, "Error: Fork failed\n");
		else
		{
			wait(NULL);
		}
		free(full_path);
	}

	return (0);
}
