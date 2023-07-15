#include "shell.h"
/**
* main - the main program
* Return: 0
*/
int main(void)
{
char command[1024];
char **parsed_command;
while (1)
{
prompt();
read_command(&command);
parsed_command = parse_command(command);
if (parsed_command[0] != NULL)
{
execute_command(parsed_command);
}
}
return (0);
}
