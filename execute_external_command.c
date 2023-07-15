#include "shell.h"

void execute_external_command(char **command)
{
pid_t child_pid = fork();
if (child_pid == -1)
{
handle_error();
}
else if (child_pid == 0)
{
if (command[0][0] != '/')
{
char *cmd_path = malloc(strlen(command[0]) + 6);
if (cmd_path == NULL)
{
fprintf(stderr, "Error: failed to allocate memory\n");
exit(EXIT_FAILURE);
}
sprintf(cmd_path, "/bin/%s", command[0]);
free(command[0]);
command[0] = cmd_path;
}
if (execve(command[0], command, environ) == -1)
{
perror("execve");
_exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}
}
