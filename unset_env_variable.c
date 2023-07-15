#include "shell.h"
/**
 * unset_env_variable - function to unset an environment variable
 * @command: the command line
 * Return: 0 on success, -1 on failure
 */
int unset_env_variable(char **command)
{
if (command[1] == NULL)
{
fprintf(stderr, "Usage: unsetenv VARIABLE\n");
return (-1);
}
if (unsetenv(command[1]) == -1)
{
perror("unsetenv");
return (-1);
}
return (0);
}
