#include "shell.h"
/**
 * set_env_variable - function to set or modify an environement variable
 * @command: the command line
 * Return: 0 on success, -1 on failure
 */
int set_env_variable(char **command)
{
if (command[1] == NULL || command[2] == NULL)
{
fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
return (-1);
}
if (setenv(command[1], command[2], 1) == -1)
{
perror("setenv");
return (-1);
}
return (0);
}
