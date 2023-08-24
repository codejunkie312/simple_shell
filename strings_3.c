#include "shell.h"

/**
 * _strcspn - gets the length of a prefix substring
 * @s: string to search
 * @accept: string to match
 * Return: number of bytes in the initial seg of s
 * which consist only of bytes not from accept
 */
unsigned int _strcspn(char *s, char *accept)
{
	unsigned int i, j, hit, length;

	length = 0;
	for (i = 0; s[i]; i++)
	{
		hit = 0;
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
			{
				hit = 1;
				break;
			}
		}
		if (hit == 1)
			return (length);
		length++;
	}
	return (length);
}

/**
 * _fputc - writes a character to stdout
 * @c: character to write
 * @stream: stream to write to
 * Return: number of chars written
 */
int _fputc(int c, FILE *stream)
{
	return (write(stream->_fileno, &c, 1));
}

/**
 * _fputs - writes a string to stdout
 * @s: string to write
 * @stream: stream to write to
 * Return: number of chars written
 */
int _fputs(char *s, FILE *stream)
{
	return (write(stream->_fileno, s, _strlen(s)));
}

