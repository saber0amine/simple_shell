#include "shell.h"
/**
 * execute_command - function to execute the shell command
 * @command: the command line
 */
<<<<<<< HEAD

void execute_command(char **command) {
    if (command == NULL || command[0] == NULL) {
        // Invalid command
        return;
    }

    if (strcmp(command[0], "exit") == 0) {
        // Exit command
        handle_exit(command);
        return;
    } else if (strcmp(command[0], "env") == 0) {
        // Print environment command
        env_shell();
        return;
    }

    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        handle_relative_path(command);

        // Check if logical operators exist in the command
        int operator_index = -1;
        for (int i = 0; command[i] != NULL; i++) {
            if (strcmp(command[i], "&&") == 0 || strcmp(command[i], "||") == 0) {
                operator_index = i;
                break;
            }
        }

        if (operator_index != -1) {
            // Logical operator found
            char *operator = command[operator_index];
            command[operator_index] = NULL;  // Split the command into two parts

            // Execute the first part of the command
            if (execve(command[0], command) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        } else {
            // No logical operator, execute the command as usual
            if (execve(command[0], command) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        // Parent process
        int status;
        if (waitpid(child_pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        
        // Check the exit status of the child process
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0 && strcmp(command[0], "&&") == 0) {
                // Execute the command after &&
                int i = 0;
                while (command[i] != NULL) {
                    i++;
                }
                execute_command(&command[i + 1]);
            }
        } else {
            if (strcmp(command[0], "||") == 0) {
                // Execute the command after ||
                int i = 0;
                while (command[i] != NULL) {
                    i++;
                }
                execute_command(&command[i + 1]);
            }
        }
    }
}   

=======
void execute_command(char **command)
{
if (strcmp(command[0], "exit") == 0)
{
exit_shell();
}
else if (strcmp(command[0], "env") == 0)
{
env_shell();
}
else if (strcmp(command[0], "setenv") == 0)
{
if (set_env_variable(command) == -1)
fprintf(stderr, "Failed to set environment variable\n");
return;
}
else if (strcmp(command[0], "unsetenv") == 0)
{
if (unset_env_variable(command) == -1)
fprintf(stderr, "Failed to unset environment variable\n");
return;
}
else if (strcmp(command[0], "cd") == 0)
{
if (command[1] != NULL)
change_directory(command[1]);
else
change_directory(getenv("HOME"));
return;
}
else
{
execute_external_command(command);
return;
}
}
>>>>>>> origin/master
