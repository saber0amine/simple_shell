#include "main.h"

/**
 * _printf - print a string to stander out put
 * @str: string input
 * Return: void
 */
void _printf(const char *str)
{
        if (!str)
                return;
        while (*str)
        {
                write(STDOUT_FILENO, str, 1);
                str++;
        }
}

/**
 * cleanUpArray - free an array of pointers
 * @array: array of pointers
 * Return: void
 */
void cleanUpArray(char **array)
{
        int i;

        if (!array)
                return;

        for (i = 0; array[i]; i++)
        {
                free(array[i]);
                array[i] = NULL;
        }

        free(array);
}

/**
 * splitFunc - splitFunc a given string by a delimiter
 * @d: data struct input
 * @delim: string input
 * Return: void
 */
void splitFunc(data *d, const char *delim)
{
        char *token;
        int ntoken = 0;

        d->av = malloc(2 * sizeof(char *));
        if (d->av == NULL)
        {
                free(d->cmd);
                perror(d->shell_name);
                exit(EXIT_FAILURE);
        }
        d->av[0] = NULL;
        d->av[1] = NULL;

        token = strtok(d->cmd, delim);
        while (token)
        {
                d->av = realloc(d->av, (ntoken + 2) * sizeof(char *));
                if (d->av == NULL)
                        goto free;
                d->av[ntoken] = _strdup(token);
                if (d->av[ntoken] == NULL)
                        goto free;
                ntoken++;
                token = strtok(NULL, delim);
        }
        d->av[ntoken] = NULL;
        return;
free:
        cleanUpArray(d->av);
        free(d->cmd);
        perror(d->shell_name);
        exit(EXIT_FAILURE);
}

/**
 * initDataFunc - init data
 * @d: data struct input
 * @shell_name: string input
 * Return: void
 */

void initDataFunc(data *d, const char *shell_name)
{
        d->cmd = NULL;
        d->av = NULL;
        d->shell_name = shell_name;
        d->last_exit_status = EXIT_SUCCESS;
        d->flagsetenvFunction = 0;
}

/**
 * InterpretCmd - get the commend from the prompt and structure it into data struct
 * @d: data struct input
 * Return: void
 */
void InterpretCmd(data *d)
{
        size_t n = 0;
        ssize_t nread;
        int i = 0;

        nread = _getline(&d->cmd, &n, stdin);

        if (nread == -1)
        {
                free(d->cmd);
                exit(EXIT_SUCCESS);
        }

        d->cmd[nread - 1] = '\0';
        _functionTrimage(d->cmd);
        /* replace hashtag with end of line we can also do it with strtok*/
        for (i = 0; d->cmd[i] != '\0'; i++)
        {
                if (d->cmd[0] == '#' || (d->cmd[i] == '#' && d->cmd[i - 1] == ' '))
                {
                        d->cmd[i] = '\0';
                        break;
                }
        }
        _functionTrimage(d->cmd);
}
