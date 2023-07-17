#include "shell.h"

/**
 * _execommand - is the function thet execute the command
 * @array: is the arra where the command and arg stored
 * @command: is the string that the user write in input
 * Return: return the status
 */

int _execommand(char *command, char **array)
{
	pid_t c_pid;
	int status = 0;

	c_pid = fork();
	if (c_pid == -1)
	{
		perror("c_pid");
		free_array(array);
		free(command);
		exit(EXIT_FAILURE);
	}
	if (c_pid == 0)
	{
		if (execve(array[0], array, NULL) == -1)
		{
			perror("execve");
			free_array(array);
			free(command);
			exit(EXIT_FAILURE);
		}
	}
	else if (wait(&status) == -1)
	{
		perror("ppid");
		free_array(array);
		free(command);
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

