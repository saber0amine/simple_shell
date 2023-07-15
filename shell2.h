#ifndef SHELL2_H
#define SHELL2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char **environ;

void change_directory(const char *directory);
void env_shell(void);
void execute_command(char **command);
char **parse_command(char *command_line);
void shell_loop(void);
int main(int argc, char **argv);

#endif /* SHELL2_H */
