#include "shell.h"

/**
 * run_builtin - function run built command
 * @array: get command in array
 * @command: is the str that the user inter in input
 * Return: return 1 if success or 0 if not
 */
int run_builtin(char **array, char *command)
{
	if (strcmp(array[0], "exit") == 0)
	{
		exit_builtin(array, command);
		return (1);
	}
	if (strcmp(array[0], "env") == 0)
	{
		env_builtin();
		return (1);
	}
	if (strcmp(array[0], "setenv") == 0)
	{
		set_builtin(array);
		return (1);
	}
	if (strcmp(array[0], "unsetenv") == 0)
	{
		unset_builtin(array);
		return (1);
	}
	return (0);
}

/**
 * exit_builtin - is the function that exit the shell
 * @array: is the array where is the commend stored
 * @command: is the str that the user inter in input
 */

void exit_builtin(char **array, char *command)
{
	int status = 0;
	const char *errstr = "./hsh: 1: exit: Illegal number: ";

	if (array[1])
	{
		if (_isnumber(array[1]))
			status = atoi(array[1]);
		else
		{
			write(STDERR_FILENO, errstr, strlen(errstr));
			write(STDERR_FILENO, array[1], _strlen(array[1]));
			write(STDERR_FILENO, "\n", 1);
			status = 2;
		}
	}
	free_array(array);
	free(command);
	exit(status);
}

/**
 * env_builtin - is the function that print the env
 */

void env_builtin(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * set_builtin - create a new variable or modify an existing one
 * @array: is the array where data stored
 */

void set_builtin(char **array)
{
	if (array[1] && array[2])
	{
		if (_setenv(array[1], array[2]) == -1)
		{
			perror("setenv");
		}
	}
}

/**
 * unset_builtin - Remove an environment variable
 * @array: is the array where data stored
 */

void unset_builtin(char **array)
{
	int i, j;
	int len;

	if (!array[1] || !_getenv(array[1]))
	{
		perror(array[0]);
		return;
	}
	len = _strlen(array[1]);
	for (i = 0; environ[i]; i++)
		if (strncmp(environ[i], array[1], len) == 0 && environ[i][len] == '=')
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
}
