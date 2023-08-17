#include "shell.h"

/**
 * find_path - find command in path env variable
 * @command: user input
 * Return: NULL if not command found
 */
char *find_path(char *command)
{
	char *path_env = getenv("PATH");
	char *PATH = strdup(path_env);
	char *path = strtok(PATH, ":");
	char *full_path = malloc(1024);

	while (path != NULL)
	{
		sprintf(full_path, "%s/%s", path, command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		path = strtok(NULL, ":");
	}
	free(full_path);
	return (NULL);
}

/**
 * print_env - prints the environment variables
 * Return: nothing
 */
void print_env(void)
{
	char **env;

	for (env = environ; *env != 0; env++)
		printf("%s\n", *env); 
}
