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

/**
 * _fprintf - prints to stderr
 * @stream: stream to print to
 * @format: format to print
 * ...
 * Return: number of chars printed
 */
int _fprintf(FILE *stream, const char *format, ...)
{
	va_list args;
	int i, j, len;
	char *s;

	va_start(args, format);
	i = 0;
	j = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
				case 'c':
					_fputc(va_arg(args, int), stream);
					j++;
					break;
				case 's':
					s = va_arg(args, char *);
					len = _strlen(s);
					_fputs(s, stream);
					j += len;
					break;
				case '%':
					_fputc('%', stream);
					j++;
					break;
			}
			i++;
		}
		else
		{
			_fputc(format[i], stream);
			j++;
		}
		i++;
	}
	return (j);
}


