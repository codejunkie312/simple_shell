#include "shell.h"

/**
 * command_loop - main command loop
 * Return: 0 on Success
 */
int command_loop(void)
{
	char *command, *pwd, *new_line;

	while (1)
	{
		pwd = _getenv("PWD");
		if (isatty(STDIN_FILENO))
			_fprintf(stdin, "($) %s ", pwd);
		command = _getline(stdin);
		if (command == NULL)
		{
			_fprintf(stdin, "\n");
			break;
		}
		else if (_strcmp(command, "No_command") == 0)
			continue;

		new_line = _strchr(command, '\n');
		if (new_line != NULL)
			*new_line = '\0';

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
	char *full_path = NULL;
	pid_t pid;

	parse_command(command, argv);
	if (!handle_sepcial_commands(argv))
	{
		if (access(argv[0], X_OK) != 0)
			full_path = find_path(argv[0]);
		if (full_path == NULL && access(argv[0], X_OK) != 0)
		{
			_fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
			return (127);
		}
		if (access(argv[1], X_OK) != 0)
			status = 2;
		pid = fork();
		if (pid == 0)
		{
			if (execve(full_path ? full_path : command, argv, NULL) == -1)
			{
				perror("execve");
				free(full_path);
				exit(127);
			}
		}
		else if (pid < 0)
			perror("fork");
		else
			waitpid(pid, &status, 0);
		if (full_path)
			free(full_path);
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

	if (argv[0] == NULL)
		return (1);
	if (_strcmp(argv[0], "exit") == 0)
	{
		status = 0;
		if (argv[1] != NULL)
		{
			status = _atoi(argv[1]);
			if (status < 0)
			{
				_fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
				argv[0], getpid(), argv[1]);
				return (2);
			}
		}
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
