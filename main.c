#include "shell.h"

/**
 * main - Toggles a shell interperter
 * Return: void
 */
int main(void)
{
	char command[100];

	while (1)
	{
		printf("($) ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			break;
		}

		command[strcspn(command, "\n")] = 0;
		if (strcmp(command, "exit") == 0)
		{
			break;
		}
	}

	return (0);
}
