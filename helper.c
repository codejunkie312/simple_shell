#include "shell.h"

static char *save; /* used by _strtok */
static char *save1; /* used by _strtok1 */

/**
 * find_path - find command in path env variable
 * @command: user input
 * Return: NULL if not command found
 */
char *find_path(char *command)
{
	char *path_env = _getenv("PATH");
	char *PATH = _strdup(path_env);
	char *path = _strtok(PATH, ":");
	char *full_path = malloc(1024);

	if (_strchr(command, '/') != NULL || _strchr(command, '.') != NULL)
	{
		if (access(command, X_OK) == 0)
		{
			free(PATH);
			free(full_path);
			return (command);
		}
		else
		{
			free(PATH);
			free(full_path);
			return (NULL);
		}
	}

	while (path != NULL)
	{
		_sprintf(full_path, "%s/%s", path, command);
		if (access(full_path, X_OK) == 0)
		{
			free(PATH);
			return (full_path);
		}
		path = _strtok(NULL, ":");
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
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_fprintf(stdout, "%s\n", environ[i]);
	}

}

/**
 * _getline - reads line from file stream
 * @stream: the stream file to read from
 * Return: length of the line
 */
char *_getline(FILE *stream)
{
	int c;
	static char buffer[BUFFER_SIZE * 10];
	static int buffer_pos;

	buffer_pos = 0;

	while ((c = _fgetc(stream)) != EOF && c != '\n')
	{
		if (buffer_pos + 1 >= (BUFFER_SIZE * 10))
		{
			_fprintf(stderr, "buffer overflow\n");
			return (NULL);
		}
		buffer[buffer_pos++] = c;
	}
	if (buffer_pos == 0 && c != EOF)
		return ("No_command");

	if (buffer_pos == 0 && (c == EOF || c == '\n'))
		return (NULL);
	buffer[buffer_pos] = '\0';

	return (buffer);
}

/**
 * _strtok - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter
 * Return: pointer to the next token
 */
char *_strtok(char *str, char *delim)
{
	char *end;

	if (str == NULL)
		str = save;
	if (*str == '\0')
	{
		save = str;
		return (NULL);
	}
	str += _strspn(str, delim);
	if (*str == '\0')
	{
		save = str;
		return (NULL);
	}
	end = str + _strcspn(str, delim);
	if (*end == '\0')
	{
		save = end;
		return (str);
	}
	*end = '\0';
	save = end + 1;
	return (str);
}

/**
 * _strtok1 - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter
 * Return: pointer to the next token
 */
char *_strtok1(char *str, char *delim)
{
	char *end;

	if (str == NULL)
		str = save1;
	if (*str == '\0')
	{
		save1 = str;
		return (NULL);
	}
	str += _strspn(str, delim);
	if (*str == '\0')
	{
		save1 = str;
		return (NULL);
	}
	end = str + _strcspn(str, delim);
	if (*end == '\0')
	{
		save1 = end;
		return (str);
	}
	*end = '\0';
	save1 = end + 1;
	return (str);
}
