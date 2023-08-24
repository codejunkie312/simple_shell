#include "shell.h"

/**
 * handle_logical_operators - handles the logic operators
 * @command_iterator: command iterator
 * Return: nothing
 */
void handle_logical_operators(char *command_iterator)
{
	int prev_status = 0;
	char *command;
	int current_status;
	char *logical_token = _strtok2(command_iterator, "&&||");

	while (logical_token != NULL)
	{
		command = trim_spaces(logical_token);
		current_status = execute_command(command);

		if (prev_status == 0 && _strcmp(logical_token, "&&") == 0)
			break;
		else if (prev_status != 0 && _strcmp(logical_token, "||") == 0)
			break;
		prev_status = current_status;
		logical_token = _strtok2(NULL, "&&||");
	}
}
