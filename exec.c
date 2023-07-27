#include "main.h"

/**
 * run_pros - is the function to run the prosses
 * @d: is the data
 * Return: void
 */

void run_pros(data *d)
{
	pid_t child_pid = fork();
	int status = 0;

	if (child_pid == -1)
		goto free;
	if (child_pid == 0 && execve(d->av[0], d->av, NULL) == -1)
		goto free;
	else if (wait(&status) == -1)
		goto free;
	if (WIFEXITED(status))
		d->last_exit_status = WEXITSTATUS(status);
	return;
free:
	perror(d->shell_name);
	free_array(d->av);
	free(d->cmd);
	exit(EXIT_FAILURE);
}

/**
 * handl_signal - is the function that hundel the signal
 * @signal: is the input
 * Return: void
 */

void handl_signal(int signal)
{
	/*const char prompt[] = PROMPT;*/
	(void)signal;
	exit(EXIT_FAILURE);
	/*_printf(prompt);*/
}

/**
 * _execmd - is the function that exectute command
 * @d: is the data
 * Return: void
 */

void _execmd(data *d)
{
	const char prompt[] = PROMPT;

	signal(SIGINT, handl_signal);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_printf(prompt);

		_read_cmd(d);
		if (_strlen(d->cmd) != 0)
		{
			_splitstr(d, " ");
			if (!exec_builtin(d))
			{
				_which(d);
				if (access(d->av[0], F_OK) == -1)
				{
					perror(d->shell_name);
				}
				else
				{
					run_pros(d);
				}
			}
			free_array(d->av);
		}
		free(d->cmd);
	}
}
