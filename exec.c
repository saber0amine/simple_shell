#include "main.h"

/**
 * debutDeProcess - start a new process
 * @d: data struct input
 * Return: void
 */

void debutDeProcess(data *d)
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
        cleanUpArray(d->av);
        free(d->cmd);
        exit(EXIT_FAILURE);
}

/**
 * signeEviter - Signal handler function
 * @signal: int input
 * Return: void
 */

void signeEviter(int signal)
{
        /*const char prompt[] = PROMPT;*/
        (void)signal;
        exit(EXIT_FAILURE);
        /*_printf(prompt);*/
}

/**
 * Execute - exectute cmd
 * @d: data struct input
 * Return: void
 */

void Execute(data *d)
{
        const char prompt[] = PROMPT;

        signal(SIGINT, signeEviter);

        while (1)
        {
                if (isatty(STDIN_FILENO))
                        _printf(prompt);

                InterpretCmd(d);
                if (_strlen(d->cmd) != 0)
                {
                        splitFunc(d, " ");
                        if (!exectuteFunc(d))
                        {
                                _functionWich(d);
                                if (access(d->av[0], F_OK) == -1)
                                {
                                        perror(d->shell_name);
                                }
                                else
                                {
                                        debutDeProcess(d);
                                }
                        }
                        cleanUpArray(d->av);
                }
                free(d->cmd);
        }
}