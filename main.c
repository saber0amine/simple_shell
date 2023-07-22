#include "shell.h"

/**
 * _EOF - is the function that exit if the user type ctr+d
 * @n_chars: is the len
 * @command: is the where stored the input of the use
 */

void _EOF(int n_chars, char *command)
{
	if (n_chars == -1)
	{
		free(command);
		exit(EXIT_SUCCESS);
	}
}

/**
 * main - is the function that read and start the procec
 * @argc: is the number of arg passed to the function
 * @argv: is the arg passed inot the function
 * Return: return the status
 */

int main(int argc, char **argv)
{
	char **array = NULL, *command = NULL;
	size_t buffer_size = 0;
	ssize_t n_chars = 0;
	int status = EXIT_SUCCESS;
	(void)argc, (void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		n_chars = _getline(&command, &buffer_size, stdin);
		_EOF(n_chars, command);
		command[n_chars - 1] = '\0';
		_trim(command);
		if (strlen(command) != 0)
		{
			array = _splitstr(command, array);
			if (array == NULL)
			{
				free(command);
				continue;
			}
			if (!run_builtin(array, command))
			{
				array = _getpath(array);
				if (array == NULL)
				{
					free(command);
					continue;
				}
				if (access(array[0], F_OK) == -1)
					perror(array[0]);
				else
					status = _execommand(command, array);
			}
			free_array(array);
		}
	}
	free(command);
	return (status);
}
