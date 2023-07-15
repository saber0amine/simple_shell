#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stddef.h>

/* Prototypes */
extern char **environ;
void prompt(void);
extern char **environ;
void read_command(char (*command)[1024]);
char **parse_command(char *command);
void execute_command(char **command);
void handle_error(void);
void exit_shell(void);

void handle_exit(char **args);
void env_shell(void);
void tokenize_command(char *buffer, char **args);
void handle_relative_path(char **args);
<<<<<<< HEAD
char* my_strtok(char* str, const char* delim);
=======
int set_env_variable(char **command);
int unset_env_variable(char **command);
void execute_external_command(char **command);
void change_directory(const char *directory);
>>>>>>> origin/master


char* replace_variable(const char* input, const char* variable, const char* value);
void handle_variable_replacement(char **command , int status);
#endif
