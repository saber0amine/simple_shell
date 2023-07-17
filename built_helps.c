#include "shell.h"

/**
 * create_new_entry - create i new variable or modify an existing one
 * @key: is the key of the variable
 * @value: is the value of the variable
 * Return: return null or new_entry
 */

char *create_new_entry(char *key, char *value)
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
 * _new_environ - create a new variable or modify an existing one
 * @key: is the key of the variable
 * @value: is the value of the variable
 * Return: return new_env or NULL
 */

char **_new_environ(char *key, char *value)
{
	int env_len = 0, i = 0;
	char *new_entry;
	char **new_environ;

	while (environ[env_len])
		env_len++;
	new_entry = create_new_entry(key, value);
	if (new_entry == NULL)
		return (NULL);
	new_environ = _getenv(key) ? malloc((env_len + 1) * sizeof(char *))
								: malloc((env_len + 2) * sizeof(char *));

	if (!new_environ)
	{
		free(new_entry);
		return (NULL);
	}
	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(strlen(environ[i]) + 1);
		if (!new_environ[i])
		{
			free_array(new_environ);
			free(new_entry);
			return (NULL);
		}
		if (strncmp(environ[i], key, strlen(key)) == 0
		&& environ[i][strlen(key)] == '=')
			strcpy(new_environ[i], new_entry);
		else
			strcpy(new_environ[i], environ[i]);
	}
	if (!_getenv(key))
	{
		new_environ[env_len] = new_entry;
		new_environ[env_len + 1] = NULL;
	}
	else
		new_environ[env_len] = NULL;
	return (new_environ);
}

/**
 * _setenv - create a new variable, or modify an existing one
 * @key: is the key of the variable variable
 * @value: is the alue of the variable value
 * Return: 0 or -1
 */

int _setenv(char *key, char *value)
{
	char **new_environ;

	if (!key || !value)
		return (-1);

	new_environ = _new_environ(key, value);
	if (!new_environ)
		return (-1);
	environ = new_environ;
	/*set_status = 1;*/

	return (0);
}
