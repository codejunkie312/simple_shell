#include "shell.h"

/**
 * setenv_case - handles the setenv builtin
 * @argv: arguments
 * Return: void
 */
void setenv_case(char *argv[])
{
	if (argv[1] == NULL || argv[2] == NULL)
	{
		perror("Usage: setenv VARIABLE VALUE");
	}
	else
	{
		if (_setenv(argv[1], argv[2], 1) != 0)
		{
			perror("Failed to set environment variable");
		}
	}
}

/**
 * unsetenv_case - handles the unsetenv builtin
 * @argv: arguments
 * Return: void
 */
void unsetenv_case(char *argv[])
{
	if (argv[1] == NULL)
	{
		perror("Usage: unsetenv VARIABLE");
	}
	else
	{
		if (_unsetenv(argv[1]) != 0)
		{
			perror("Failed to unset environment variable");
		}
	}
}

/**
 * cd_case - handles the cd builtin
 * @argv: arguments
 * Return: void
 */
void cd_case(char *argv[])
{
	char *dest, *cwd;

	dest = argv[1] ? argv[1] : _getenv("HOME");
	if (dest[0] == '-' && dest[1] == '\0')
	{
		if (_getenv("OLDPWD"))
			dest = _getenv("OLDPWD");
		else
		{
			perror("cd: OLDPWD not set");
			exit(1);
		}
	}
	if (chdir(dest) != 0)
		perror("cd");
	else
	{
		cwd = getcwd(NULL, 0);
		if (_setenv("OLDPWD", _getenv("PWD"), 1) != 0 || _setenv("PWD", cwd, 1) != 0)
			perror("cd");
		free(cwd);
	}
}
