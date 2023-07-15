#include "shell.h"
/**
 * parse_command - the function to parse the command on terminal
 * @command: the CLI
 * Return: args
 */

char **parse_command(char *command) {
    char *buffer = strdup(command);
    char **args = malloc(sizeof(char *) * 1024);
    if (args == NULL) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    int arg_index = 0;
    char *token = my_strtok(buffer, " \n");
    while (token != NULL) {
        if (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0) {
            // Handle && and || as separate arguments
            args[arg_index++] = strdup(token);
        } else {
            args[arg_index++] = strdup(token);
        } 
        token = my_strtok(NULL, " \n");
    }
    args[arg_index] = NULL;
    free(buffer);

    return args;
}