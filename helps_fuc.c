#include "shell.h"

/**
 * free_array - is the function that free array
 * @array: is the array we want to free
 */

void free_array(char **array)
{
	int i = 0;

	if (array == NULL)
		return;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}


/**
 * _trim - remove leading and trailing spaces and tabs from a string
 * @str: string input
 * Return: void.
 */

void _trim(char *str)
{
	int i, j, len = _strlen(str);

	for (i = 0; i < len && (str[i] == ' ' || str[i] == '\t'); i++)
		;

	for (j = 0; i < len ; i++, j++)
		str[j] = str[i];

	str[j] = '\0';

	for (i = _strlen(str) - 1; i > 0 && (str[i] == ' ' || str[i] == '\t'); i--)
		str[i] = '\0';
}

/**
 * _isnumber - check if a string is a number
 * @status: string to be checked
 * Return: void
 */
int _isnumber(const char *status)
{
	if (status == NULL || status[0] == '\0')
		return (0);
	while (*status)
	{
		if (!_isdigit(*status))
			return (0);
		status++;
	}
	return (1);
}

/**
 * _isdigit - check if charachter is number
 * @c: charachter
 * Return: 1 if its a digit 0 otherwise
 */
int _isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
