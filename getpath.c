#include "shell.h"

/**
 * makepath - is the function that build the command path
 * @token: is the path of the command
 * @cmd: is the command from input
 * @all_paths: is all the path
 * Return: return the full path of the command
 */

char *makepath(char *token, char *cmd, char *all_paths)
{
	size_t token_len;
	char *path;

	token_len = _strlen(token) + _strlen(cmd) + 2;
	path = malloc(token_len);
	if (path == NULL)
	{
		free(all_paths);
		return (NULL);
	}
	_strcpy(path, token);
	_strcat(path, "/");
	_strcat(path, cmd);

	return (path);
}

/**
 * _getpath - id the function that return the full path of the command
 * @array: is the array where stored the command
 * Return: return full path command or NULL
 */

char **_getpath(char **array)
{
	char *token, *path, *all_paths, *env_path = _getenv("PATH");

	if (array == NULL || array[0] == NULL)
		return (NULL);
	if (env_path == NULL)
	{
		all_paths = malloc(2);
		if (all_paths == NULL)
			return (NULL);
		all_paths[0] = '\0';
	}
	else
	{
		all_paths = malloc(_strlen(env_path) + 2);
		if (all_paths == NULL)
			return (NULL);
		_strcpy(all_paths, env_path);
	}
	if (all_paths == NULL)
		return (NULL);
	token = _strtok(all_paths, ":");
	while (token)
	{
		path = makepath(token, array[0], all_paths);
		if (access(path, F_OK) == 0)
		{
			free(array[0]);
			array[0] = _strdup(path);
			free(path);
			break;
		}
		free(path);
		token = _strtok(NULL, ":");
	}
	free(all_paths);
	return (array);
}
