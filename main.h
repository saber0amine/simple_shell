#ifndef MAIN_H
#define MAIN_H


#define PROMPT "$ "

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

extern char **environ;

/**
 * struct data - is the struct contian data.
 * @av: is the argv
 * @cmd: is the command
 * @shell_name: is the name of the shell
 * @last_exit_status: is the last exit status
 * @flag_setenv: we use it to free memory
 */
typedef struct data
{
	char **av;
	char *cmd;
	const char *shell_name;
	int last_exit_status;
	int flag_setenv;
} data;

/**
 * struct builtin - this is the builtin cd and echo ...
 * @cmd: is the command
 * @f: is the functions of builtin cmd
 */
typedef struct builtin
{
	const char *cmd;
	void (*f)(data *d);
} builtin;

int exec_builtin(data *d);
void exit_builtin(data *d);
void env_builtin(data *d);
void setenv_builtin(data *d);
void unsetenv_builtin(data *d);
void cd_builtin(data *d);
void echo_builtin(data *d);

void _printf(const char *str);
void free_array(char **array);
void _splitstr(data *d, const char *delim);
void initial_data(data *d, const char *shell_name);
void _read_cmd(data *d);

void _perror(const char *str1, const char *str2);
void _trim_str(char *str);
void *_realloc(void *ptr, unsigned int new_size);

void run_pros(data *d);
void handl_signal(int sig);
void _execmd(data *d);

char *_getenv(char *key);
int _which(data *d);
int _setenv(data *d, char *key, char *value);

unsigned int _strlen(char *str);
int _strcmp(const char *str1, const char *str2);
int _strncmp(const char *str1, const char *str2, int n);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);

char *_strdup(const char *str);
int _isnumber(const char *status);
int _isdigit(int c);

#define READ_BUF_SIZE 1024

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);


#endif
