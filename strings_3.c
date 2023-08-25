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

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 * Return: pointer to the new string
 */
char *_strdup(char *str)
{
	char *dup;
	int i, len;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

/**
 * _fgetc - reads a character from a stream
 * @stream: stream to read from
 * Return: character read
 */
int _fgetc(FILE *stream)
{
	char c;

	if (read(stream->_fileno, &c, 1) == 0)
		return (EOF);
	return (c);
}


