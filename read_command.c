#include "shell.h"
/**
 * read_command - function to read command
 * @command: the command ine to read
 */
void read_command(char (*command)[1024]) {
    size_t len;
    if (fgets(*command, 1024, stdin) == NULL) {
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            fprintf(stderr, "Error: failed to read command\n");
            exit(EXIT_FAILURE);
        }
    }
    len = strlen(*command);

    if ((*command)[len - 1] == '\n') {
        (*command)[len - 1] = '\0';
    }
}