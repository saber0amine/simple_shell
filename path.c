#include "main.h"

/**
 * _getenv - is the function that get the environment variable.
 * @key: is the key of the variable
 * Return: value of an environment variable
 */

char *_getenv(char *key)
{
	int i = -1;
	size_t key_len;

	if (key == NULL || *key == '\0')
		return (NULL);
	if (environ == NULL)
		return (NULL);

	key_len = _strlen(key);

	while (environ[++i])
	{
		if (!_strncmp(environ[i], key, key_len) && environ[i][key_len] == '=')
		{
			return (environ[i] + key_len + 1);
		}
	}
	return (NULL);
}

/**
 * _which - is the function that alocate the path of the command
 * @d: is the data
 * Return: void
 */
int _which(data *d)
{
	char *token, *path,
		*paths = malloc(_strlen(_getenv("PATH") ? _getenv("PATH") : "") + 1);
	size_t token_len;
	int find = -1;

	if (!_getenv("PATH"))
		goto step_out;
	_strcpy(paths, _getenv("PATH"));
	if (paths == NULL)
		goto step_out;
	token = strtok(paths, ":");
	while (token)
	{
		token_len = _strlen(token) + _strlen(d->av[0]) + 2;
		path = malloc(token_len);
		if (path == NULL)
			return (find);
		_strcpy(path, token);
		_strcat(path, "/");
		_strcat(path, d->av[0]);
		if (access(path, F_OK) == 0)
		{
			free(d->av[0]);
			d->av[0] = _strdup(path);
			free(path);
			find = 0;
			break;
		}
		free(path);
		token = strtok(NULL, ":");
	}
step_out:
	free(paths);
	return (find);
}

/**
 * new_entry - is the function that create a new entry
 * @key: is the key
 * @value: is the value of the variabl
 * Return: void
 */
char *new_entry(char *key, char *value)
{
	size_t new_len = strlen(key) + strlen(value) + 2;
	char *new_entry = malloc(new_len);

	if (new_entry == NULL)
		return (NULL);

	strcpy(new_entry, key);
	strcat(new_entry, "=");
	strcat(new_entry, value);

	return (new_entry);
}

/**
 * _new_environ - is the functio for the new environ
 * @key: is the key
 * @value: is the value of the variabl
 * Return: void
 */
char **_new_environ(char *key, char *value)
{
	int env_len = 0, i = 0;
	char *entry_n;
	char **new_environ;

	while (environ[env_len])
		env_len++;
	entry_n = new_entry(key, value);
	if (entry_n == NULL)
		return (NULL);
	new_environ = _getenv(key) ? malloc((env_len + 1) * sizeof(char *))
								: malloc((env_len + 2) * sizeof(char *));

	if (!new_environ)
	{
		free(entry_n);
		return (NULL);
	}
	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(strlen(environ[i]) + 1);
		if (!new_environ[i])
		{
			free_array(new_environ);
			free(entry_n);
			return (NULL);
		}
		if (strncmp(environ[i], key, strlen(key)) == 0
		&& environ[i][strlen(key)] == '=')
			strcpy(new_environ[i], entry_n);
		else
			strcpy(new_environ[i], environ[i]);
	}
	if (!_getenv(key))
	{
		new_environ[env_len] = entry_n;
		new_environ[env_len + 1] = NULL;
	}
	else
		new_environ[env_len] = NULL;
	return (new_environ);
}

/**
 * _setenv - is the function to set a new value to key
 * @d: is the data
 * @key: is the key
 * @value: is the value of the variable
 * Return: void
 */
int _setenv(data *d, char *key, char *value)
{
	char **new_environ;

	if (!key || !value)
		return (-1);

	new_environ = _new_environ(key, value);
	if (!new_environ)
		return (-1);
	environ = new_environ;
	d->flag_setenv = 1;

	return (0);
}
