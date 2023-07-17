#include "shell.h"
/**
 * _strtok - do the same whsat strtok do
 * @str: string
 * @delim: delimeter
 * Return: returning
 */
char *_strtok(char *str, const char *delim)
{
	static char *token;
	char *final_str;

	if (str)
		token = str;
	else if (!token)
		return (NULL);
	for (; *token != '\0' && strchr(delim, *token) != NULL;)
		++token;
	if (*token == '\0')
		return (NULL);
	final_str = token;
	while (*token != '\0' && strchr(delim, *token) == NULL)
		++token;
	if (*token != '\0')
		*token++ = '\0';
	return (final_str);
}
