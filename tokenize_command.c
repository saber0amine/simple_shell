<<<<<<< HEAD
#include "shell.h"
/**
 * tokenize_command - function to tokenize the command string
 * @buffer: the command string
 * @args: the array to store tokens
 */
void tokenize_command(char *buffer, char **args)
{
char *token;
int i = 0;
token = my_strtok(buffer, " \n");
while (token != NULL)
{
args[i++] = strdup(token);
token = my_strtok(NULL, " \n");
}
args[i] = NULL;
}
=======
#include "shell.h"
/**
 * tokenize_command - function to tokenize the command string
 * @buffer: the command string
 * @args: the array to store tokens
 */
void tokenize_command(char *buffer, char **args) {
    char *token;
    int i = 0;

    token = my_strtok(buffer, " \n");
    while (token != NULL) {
        if (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0) {
            // Handle && and || as separate arguments
            args[i++] = token;
        } else {
            args[i++] = strdup(token);
        }
        token = my_strtok(NULL, " \n");
    }
    args[i] = NULL;
}
>>>>>>> master
