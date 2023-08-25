#include "shell.h"

/**
 * _strcmp - returns the difference in ASCII values of two strings
 * @s1: first string
 * @s2: second string
 * Return: an int
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

/**
 * _atoi - converts char to number
 * @s: a string pointer
 * Return: int
 */

int _atoi(char *s)
{
	int sign, numStarted, i;
	unsigned int result;

	result = 0;
	sign = 1;
	numStarted = 0;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			numStarted = 1;
			result = result * 10 + (s[i] - '0');
		}
		else if ((s[i] == '-' || s[i] == '+') && !numStarted)
		{
			if (s[i] == '-')
				sign = -sign;
		}
		else if (numStarted)
			break;
	}
	return (result * sign);
}

/**
 * _strlen - returns the lenght of a string
 * @s: a string of chars
 * Return: an int
 */

int _strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * _strchr - Findd char and returns pointer to it
 * @s: a pointer for a buffer to look in
 * @c: char to look for
 * Return: a pointer
 */

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}

	if (*s == c)
		return (s);
	return (NULL);
}

/**
 * _sprintf - prints a string to stdout
 * @str: string to print
 * @format: format of the string
 * @...: arguments
 * Return: number of chars printed
 */
int _sprintf(char *str, const char *format, ...)
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
					str[j] = va_arg(args, int);
					j++;
					break;
				case 's':
					s = va_arg(args, char *);
					len = _strlen(s);
					_strcpy(str + j, s);
					j += len;
					break;
				case '%':
					str[j] = '%';
					j++;
					break;
			}
			i++;
		}
		else
		{
			str[j] = format[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	va_end(args);
	return (j);
}
