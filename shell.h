#ifndef SHELL_H
#define SHELL_H


#define PROMPT "#csisfun$ "

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

extern char **environ;

int _execommand(char *command, char **array);
char *_getenv(const char *name);
char **_getpath(char **array);
char **_splitstr(char *command, char **array);

int run_builtin(char **array, char *command);
void exit_builtin(char **array, char *command);
void env_builtin(void);
int _setenv(char *key, char *value);
char **_new_environ(char *key, char *value);
char *create_new_entry(char *name, char *value);
void unset_builtin(char **array);
void set_builtin(char **array);

void free_array(char **array);
void _trim(char *str);
int _isnumber(const char *status);
int _isdigit(int c);

int _strlen(char *str);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strncmp(char *fstr, char *sstr, int n);

/*ssize_t _getline(char **bufferptr, size_t *buf_size, FILE *stream);*/
#define READ_BUF_SIZE 1024
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int _oldsize, unsigned int _newsize);
void assign_buf(char **buf_ptr, size_t *size_bufp, char *buf, size_t size_buf);

char *_strtok(char *str, const char *delim);

#endif
