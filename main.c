#include "shell.h"

/**
 * main - Toggles a shell interperter
 * Return: 1 if failed, 0 if successful
 */
int main(void)
{
	char *command;
	char *argv[100];
	char *token, *full_path;
	int i, status;
	pid_t pid;

	argv[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");
		command = _getline(stdin);
		
		token = _strtok(command, " ");
		i = 0;
		while (token != NULL)
		{
			argv[i] = token;
			i++;
			token = _strtok(NULL, " ");
		}

		argv[i] = NULL;
		if (command == NULL)
			break;
		if (strcmp(command, "exit") == 0)
		{
			status = 0;
			if (argv[1] != NULL)
				status = atoi(argv[1]);
			exit(status);
		}
		else if (strcmp(command, "env") == 0)
		{
			print_env();
			continue;
		}
		else if (strcmp(argv[0], "setenv") == 0)
		{
			if (argv[1] == NULL || argv[2] == NULL)
			{
				fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
				continue;
			}
			else
			{
				if (setenv(argv[1], argv[2], 1) != 0)
				{
					fprintf(stderr, "Failed to set environment variable\n");
					continue;
				}
				continue;
			}
		}
		else if (strcmp(argv[0], "unsetenv") == 0)
		{
			if (argv[1] == NULL)
			{
				fprintf(stderr, "Usage: unsetenv VARIABLE\n");
				continue;
			}
			else
			{
				if (unsetenv(argv[1]) != 0)
				{
					fprintf(stderr, "Failed to unset environment variable\n");
					continue;
				}
				continue;
			}
		}
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
