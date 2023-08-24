#include "shell.h"

/**
 * _setenv - sets an environment variable
 * @name: name of the variable
 * @value: value of the variable
 * @overwrite: overwrite flag
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *name, const char *value, int overwrite)
{
	char *new_var;
	int i, len, found = 0;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	if (value == NULL)
		value = "";
	len = _strlen(value);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0)
		{
			found = 1;
			if (overwrite)
			{
				new_var = malloc(_strlen(name) + len + 2);
				if (new_var == NULL)
					return (-1);
				_sprintf(new_var, "%s=%s", name, value);
				environ[i] = new_var;
			}
			break;
		}
	}
	if (!found)
	{
		new_var = malloc(_strlen(name) + len + 2);
		if (new_var == NULL)
			return (-1);
		_sprintf(new_var, "%s=%s", name, value);
		environ[i] = new_var;
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
