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
	char *new_dir;
	char old_dir[1024];
	char new_pwd[1024];
	char temp[1024];

	new_dir = argv[1];
	getcwd(old_dir, sizeof(old_dir));

	if (new_dir == NULL)
		new_dir = _getenv("HOME");
	else if (_strcmp(new_dir, "-") == 0)
		new_dir = _getenv("OLDPWD");
	else if (new_dir[0] != '/')
	{
		_sprintf(temp, "%s/%s", old_dir, new_dir);
		new_dir = temp;
	}

	if (chdir(new_dir) != 0)
		perror("cd");
	else
	{
		getcwd(new_pwd, sizeof(new_pwd));
		_setenv("PWD", new_pwd, 1);
		_setenv("OLDPWD", old_dir, 1);
	}
}

