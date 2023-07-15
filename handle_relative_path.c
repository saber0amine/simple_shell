#include "shell.h"
/**
 * handle_relative_path - function to handle relative path of the command
 * @args: the array of command tokens
 */
void handle_relative_path(char **args)
{
if (args[0][0] != '/')
{
char *cmd_path = malloc(strlen(args[0]) + 6);
if (cmd_path == NULL)
{
fprintf(stderr, "Error: failed to allocate memory\n");
exit(EXIT_FAILURE);
}
sprintf(cmd_path, "/bin/%s", args[0]);
free(args[0]);
args[0] = cmd_path;
}
<<<<<<< HEAD
}
=======
}

>>>>>>> master
