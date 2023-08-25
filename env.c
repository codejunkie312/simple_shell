#include "shell.h"

/**
 * _setenv - sets an environment variable
 * @name: name of the variable
 * @value: value of the variable
 * @overwrite: overwrite flag
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *name, char *value, int overwrite)
{
	int i, found = 0;
	char *newvar;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	if (value == NULL)
		value = "";
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0)
		{
			found = 1;
			if (overwrite)
			{
				newvar = malloc(_strlen(name) + _strlen(value) + 2);
				if (newvar == NULL)
					return (-1);
				_strcpy(newvar, name);
				_strcat(newvar, "=");
				_strcat(newvar, value);
				environ[i] = newvar;
			}
			break;
		}
	}
	if (!found)
	{
		newvar = malloc(_strlen(name) + _strlen(value) + 2);
		if (newvar == NULL)
			return (-1);
		_strcpy(newvar, name);
		_strcat(newvar, "=");
		_strcat(newvar, value);
		environ[i] = newvar;
		environ[i + 1] = NULL;
	}
	return (0);
}

/**
 * _unsetenv - unsets an environment variable
 * @name: name of the variable
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(char *name)
{
	int i, j, found = 0;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0)
		{
			found = 1;
			free(environ[i]);
			for (j = i; environ[j] != NULL; j++)
				environ[j] = environ[j + 1];
			break;
		}
	}
	if (!found)
		return (-1);
	return (0);
}

/**
 * _getenv - gets an environment variable
 * @name: name of the variable
 * Return: pointer to the value of the variable, NULL if not found
 */
char *_getenv(char *name)
{
	int i;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0)
			return (environ[i] + _strlen(name) + 1);
	}
	return (NULL);
}
