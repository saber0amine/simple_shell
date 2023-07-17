#include "shell.h"
/**
 * _getenv - function to get path envirenment.
 * @name: name of env
 * Return: rtrn 0
 */
char *_getenv(const char *name)
{
	int i = 0, j;
	char *value;
	char **env = environ;

	if (!name)
		return (NULL);
	while (env[i])
	{
		j = 0;
		if (name[j] == env[i][j])
		{
			while (name[j])
			{
				if (name[j] != env[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (env[i] + j + 1);
				return (value);
			}
		}
		i++;
	}
	return (0);
}
