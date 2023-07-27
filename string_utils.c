#include "main.h"

/**
 * _strlen - this function return length of a string
 * @str: the string
 * Return: len of string.
 */

unsigned int _strlen(char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}


/**
 * _strcmp - this function compares two strings.
 * @str1: string 1
 * @str2: string 2
 * Return: the result
 */
int _strcmp(const char *str1, const char *str2)
{
	int i;
	int res = 0;

	for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
		{
			res = str1[i] - str2[i];
			break;
		}
	}

	return (res);
}

/**
 * _strncmp - this function compares two strings with a number
 * @str1: string 1
 * @str2: string 2
 * @n: how many char you want compare
 * Return: the result
 */
int _strncmp(const char *str1, const char *str2, int n)
{
	int i;
	int res = 0;

	for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
	{

		if (i >= n)
			break;
		if (str1[i] != str2[i])
		{
			res = str1[i] - str2[i];
			break;
		}
	}

	return (res);
}

/**
 * _strcpy - copy src to dest .
 *
 * @dest: input char *
 * @src: input const char *
 *
 * Return: char *
 */
char *_strcpy(char *dest, const char *src)
{
	int len;

	for (len = 0; src[len] != '\0'; ++len)
	{
		dest[len] = src[len];
	}
	dest[len] = '\0';
	return (dest);
}

/**
 * _strcat - appends the src string to the dest string,
 *
 * @dest: input string
 * @src: input const string
 *
 * Return: void
 */
char *_strcat(char *dest, const char *src)
{
	char *result = dest;

	while (*dest != '\0')
		dest++;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return (result);
}
