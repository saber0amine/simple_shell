#include "shell.h"


void handle_variable_replacement(char **command, int status) {
    int i = 0;
    while (command[i] != NULL) {
        if (strcmp(command[i], "$?") == 0) {
            // Replace $? with the exit status of the previous command
            char exit_status[10];
            sprintf(exit_status, "%d", WEXITSTATUS(status));
            free(command[i]);
            command[i] = strdup(exit_status);
        } else if (strcmp(command[i], "$$") == 0) {
            // Replace $$ with the process ID of the shell
            char shell_pid[10];
            sprintf(shell_pid, "%d", getpid());
            free(command[i]);
            command[i] = strdup(shell_pid);
        } else if (strstr(command[i], "$")) {
            // Handle other variables
            char* variable = strchr(command[i], '$');
            char* value = getenv(variable + 1);
            if (value != NULL) {
                char* replaced = replace_variable(command[i], variable, value);
                free(command[i]);
                command[i] = replaced;
            }
        }
        i++;
    }
}