#include "shell.h"

void execute_cd_command(char **command)
{
if (command[1] == NULL)
{
change_directory(NULL);
}
else
{
change_directory(command[1]);
}
}
