#include "shell.h"
/**
 * _splitstr - function split command
 * @command: input command
 * @array: array to put split command
 * Return: array
 */
char **_splitstr(char *command, char **array)
{
	char *token;
	int n_token = 0;

	array = malloc(sizeof(char *) * 2);
	if (array == NULL)
	{
		free(command);
		perror("array");
		exit(EXIT_FAILURE);
	}
	array[0] = NULL;
	array[1] = NULL;

	token = strtok(command, " \n\t");
	while (token)
	{
		array = realloc(array, sizeof(char *) * (n_token + 2));
		if (array == NULL)
		{
			free_array(array);
			free(command);
			perror("array");
			exit(EXIT_FAILURE);
		}
		array[n_token] = _strdup(token);
		if (array[n_token] == NULL)
		{
			free_array(array);
			free(command);
			perror("array");
			exit(EXIT_FAILURE);
		}
		n_token++;
		token = strtok(NULL, " \n\t");
	}
	array[n_token] = NULL;
	return (array);
}
