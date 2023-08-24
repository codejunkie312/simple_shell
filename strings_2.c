#include "shell.h"

static char *save2; /* used by _strtok2 */

/**
 * _strcpy - copies src to dest
 * @dest: copied to
 * @src: copied from
 * Return: a pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	char *original_dest;

	original_dest = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

/**
 * _strncmp - compares two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 * Return: an int
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	for (i = 0; i < n && s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	if (i != n)
		return (s1[i] - s2[i]);
	return (0);
}

/**
 * _strtok2 - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter
 * Return: pointer to the next token
 */
char *_strtok2(char *str, char *delim)
{
	char *end;

	if (str == NULL)
		str = save2;
	if (*str == '\0')
	{
		save2 = str;
		return (NULL);
	}
	str += _strspn(str, delim);
	if (*str == '\0')
	{
		save2 = str;
		return (NULL);
	}
	end = str + _strcspn(str, delim);
	if (*end == '\0')
	{
		save2 = end;
		return (str);
	}
	*end = '\0';
	save2 = end + 1;
	return (str);
}

/**
 * trim_spaces - trims spaces from a string
 * @str: string to trim
 * Return: string without spaces
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str == ' ')
		str++;
	end = str + _strlen(str) - 1;
	while (*end == ' ')
		end--;
	*(end + 1) = '\0';
	return (str);
}

/**
 * _strspn - gets the length of a prefix substring
 * @s: string to look for
 * @accept: string containing the chars to match
 * Return: number of bytes in the initial seg of s
 * which consist only of bytes from accept
 */

unsigned int _strspn(char *s, char *accept)
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
				length++;
				hit = 1;
				break;
			}
		}
		if (hit == 0)
			return (length);
	}
	return (length);
}
