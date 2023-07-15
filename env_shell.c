#include "shell.h"
/**
 * env_shell - function to print the current environment
 */
void env_shell(void)
{
int i = 0;
while (environ[i] != NULL)
{
printf("%s\n", environ[i]);
i++;
}
}
