#include "shell.h"

/**
 * _strlen - get the length of a string
 * @str: string
 * Return: length of string
 */

int _strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * _strdup - function that duplicates a string
 * @str: string
 * Return: duplicated string
 */

char *_strdup(char *str)
{
	int i = 0;
	char *dup = NULL;

	if (str == NULL)
		return (NULL);
	dup = malloc(sizeof(char) * (_strlen(str) + 1));
	if (dup == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * _strcpy - function that copies a string
 * @dest: destination string
 * @src: source string
 * Return: return copied string
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - function that concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: return concatenated string
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strncmp - function that compares two strings
 * @fstr: first string
 * @sstr: second string
 * @n: is number of bytes to compare
 * Return: return 0 if good, -1 if not
 */

int _strncmp(char *fstr, char *sstr, int n)
{
	int i = 0;

	while (fstr[i] != '\0' && sstr[i] != '\0' && i < n)
	{
		if (fstr[i] != sstr[i])
			return (-1);
		i++;
	}
	if (i == n)
		return (0);
	return (-1);
}

