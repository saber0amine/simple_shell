#include "shell.h"
/**
 * exit_shell - function to exit the shell
 */
void handle_exit(char **args) {
    int status = 0;

    if (args[1] != NULL) {
        status = atoi(args[1]);
    }

    exit(status);
}
