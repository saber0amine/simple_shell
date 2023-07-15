#include "shell.h"
/**
 * change_directory - function to change from current directory
 * @directory: the folder path
 */
void change_directory(const char *directory)
{
char cwd[1024];
if (chdir(directory) == -1)
{
perror("chdir");
return;
}
if (getcwd(cwd, sizeof(cwd)) != NULL)
{
perror("getcwd");
return;
}
set_env_variable("PWD", cwd);
}
