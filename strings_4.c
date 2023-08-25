#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: string to append to
 * @src: string to append
 * Return: pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (dest[i])
		i++;
	for (j = 0; src[j]; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (dest);
}
