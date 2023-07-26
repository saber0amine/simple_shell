#include "main.h"

/**
 * exectuteFunc - check if the command is a built-in and execute it
 * @d: data struct input
 * Return: 1 if built in, 0 if not
 */
int exectuteFunc(data *d)
{
        ObjectBuilt commandObject[] = {
                {"exit", exitFunc},
                {"env", envFunc},
                {"setenv", setEnvFunc},
                {"unsetenv", unsetEnvFunc},
                {"cd", builtin_cd},
                {NULL, NULL},
        };
        int i = 0;

        for (i = 0; commandObject[i].cmd; i++)
        {
                if (_strcmp(d->av[0], commandObject[i].cmd) == 0)
                {
                        commandObject[i].f(d);
                        return (1);
                }
        }
        return (0);
}

/**
 * exitFunc
 * - exits the shell
 * @d: data struct input
 * Return: void
 */
void exitFunc(data *d)
{
        const char *errorString = "./hsh: 1: exit: Illegal number: ";

        if (d->av[1])
        {
                if (d->av[1][0] != '-' && Cnum(d->av[1]))
                        d->last_exit_status = atoi(d->av[1]);
                else
                {
                        write(STDERR_FILENO, errorString, strlen(errorString));
                        write(STDERR_FILENO, d->av[1], strlen(d->av[1]));
                        write(STDERR_FILENO, "\n", 1);
                        d->last_exit_status = 2;
                }
        }
        cleanUpArray(d->av);
        free(d->cmd);
        if (d->flagsetenvFunction)
                cleanUpArray(environ);
        exit(d->last_exit_status);
}

/**
 * envFunc
 * - prints the current environment
 * @d: data struct input
 * Return: void
 */
void envFunc(data *d)
{
        int i = 0;

        (void)d;
        while (environ[i])
        {
                _printf(environ[i]);
                _printf("\n");
                i++;
        }
}
/**
 * setEnvFunc - Initialize a new environment variable,
 * or modify an existing one
 * @d: data struct input
 * Return: void
 */

void setEnvFunc(data *d)
{
        (void)d;
        if (d->av[1] && d->av[2])
        {
                if (setenvFunction(d, d->av[1], d->av[2]) == -1)
                {
                        perror("setenv");
                }
        }
}

/**
 * unsetEnvFunc - Remove an environment variable
 * @d: data struct input
 * Return: void
 */
void unsetEnvFunc(data *d)
{
        int i, j;
        int len;

        (void)d;
        if (!d->av[1] || !getenv(d->av[1]))
        {
                _perror(d->shell_name, "variable not found.");
                return;
        }
        len = strlen(d->av[1]);
        for (i = 0; environ[i]; i++)
                if (strncmp(environ[i], d->av[1], len) == 0 && environ[i][len] == '=')
                        for (j = i; environ[j]; j++)
                                environ[j] = environ[j + 1];
}