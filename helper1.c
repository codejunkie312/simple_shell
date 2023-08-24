#include "shell.h"

/**
 * command_loop - main command loop
 * Return: 0 on Success
 */
int command_loop(void)
{
	char *command, *pwd;

	while (1)
	{
		pwd = _getenv("PWD");
		if (isatty(STDIN_FILENO))
			_fprintf(stdin, "($) %s ", pwd);
		if ((command = _getline(stdin)) == NULL)
			break;
		if (command == NULL)
			continue;
		handle_command(command);
	}
	return (0);
}

/**
 * execute_command - executes command
 * @command: Command inputed by the user into the CLI
 * Return: a status code
 */
int execute_command(char *command)
{
	char *argv[100];
	int status = 0;
	char *full_path;
	pid_t pid;

	parse_command(command, argv);
	full_path = find_path(argv[0]);
	if (full_path == NULL)
	{
		_fprintf(stderr, "%s: command not found\n", argv[0]);
		return (127);
	}

	if (!handle_sepcial_commands(argv))
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(full_path, argv, NULL) == -1)
			{
				perror("execve");
				exit(127);
			}
		}
		else if (pid < 0)
		{
			perror("fork");
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	return (status);
}

/**
 * parse_command - parses commands into argv for execution
 * @command: command to parse
 * @argv: a lisf of arguments
 * Return nothing
 */
void parse_command(char *command, char *argv[])
{
	char *token;
	int i = 0;

	token = _strtok(command, " ");
	while (token != NULL)
	{
		argv[i++] = token;
		token = _strtok(NULL, " ");
	}
	argv[i] = NULL;
}

/**
 * handle_sepcial_commands - handles special CLI commands like cd and such
 * @argv: list of arguments
 * Return: 1 if handled and 0 if not
 */
int handle_sepcial_commands(char *argv[])
{
	int status;

	if (_strcmp(argv[0], "exit") == 0)
	{
		status = 0;
		if (argv[1] != NULL)
			status = _atoi(argv[1]);
		exit(status);
	}
	else if (_strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	else if (_strcmp(argv[0], "setenv") == 0)
	{
		setenv_case(argv);
		return (1);
	}
	else if (_strcmp(argv[0], "unsetenv") == 0)
	{
		unsetenv_case(argv);
		return (1);
	}
	else if (_strcmp(argv[0], "cd") == 0)
	{
		cd_case(argv);
		return (1);
	}
	return (0);
}

/**
 * handle_command - handles command
 * @command: command to handle
 * Return: Nothing
 */
void handle_command(char *command)
{
	char *command_iterator;

	command_iterator = _strtok1(command, ";");
	while (command_iterator != NULL)
	{
		handle_logical_operators(command_iterator);
		command_iterator = _strtok1(NULL, ";");
	}
}
