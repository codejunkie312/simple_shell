#include "shell.h"

static char buffer[BUFFER_SIZE];
static int buffer_pos;
static int line_len;

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
		{
			free(PATH);
			return (full_path);
		}
		path = strtok(NULL, ":");
	}
	free(full_path);
	free(PATH);
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

/**
 * _getline - reads line from file stream
 * @stream: the stream file to read from
 * Return: length of the line
 */
char *_getline(FILE *stream)
{
	int c;

	buffer_pos = 0;

	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		if (buffer_pos + 1 >= BUFFER_SIZE)
		{
			fprintf(stderr, "Line exceeds buffer size\n");
			return (NULL);
		}
		buffer[buffer_pos++] = c;
	}

	if (buffer_pos == 0 && c == EOF)
		return (NULL);
	buffer[buffer_pos] = '\0';
	line_len = buffer_pos;

	return (buffer);
}

/**
 * _strtok - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter
 * Return: pointer to the next token
 */
char *_strtok(char *str, const char *delim)
{
	static char *save;
	char *end;

	if (str == NULL)
		str = save;
	if (*str == '\0')
	{
		save = str;
		return (NULL);
	}
	str += strspn(str, delim);
	if (*str == '\0')
	{
		save = str;
		return (NULL);
	}
	end = str + strcspn(str, delim);
	if (*end == '\0')
	{
		save = end;
		return (str);
	}
	*end = '\0';
	save = end + 1;
	return (str);
}
