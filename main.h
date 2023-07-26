#ifndef MAIN_H
#define MAIN_H


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

/**
 * struct data - holds the main data.
 * @av: Array of tokens to pass for execve
 * @cmd: The user input, the command line
 * @shell_name: The name of the shell program
 * @last_exit_status: last exit status of last command executed
 * @flagsetenvFunction: 1 if user did exec setenv (use it to free memory)
 */
typedef struct data
{
	char **av;
	char *cmd;
	const char *shell_name;
	int last_exit_status;
	int flagsetenvFunction;
} data;

/**
 * struct ObjectBuilt - holds the main data.
 * @cmd: built in cmd
 * @f: function of builtin cmd
 */
typedef struct ObjectBuilt
{
	const char *cmd;
	void (*f)(data *d);
} ObjectBuilt;

int exectuteFunc(data *d);
void exitFunc(data *d);
void envFunc(data *d);
void setEnvFunc(data *d);
void unsetEnvFunc(data *d);
void builtin_cd(data *d);


void _printf(const char *str);
void cleanUpArray(char **array);
void splitFunc(data *d, const char *delim);
void initDataFunc(data *d, const char *shell_name);
void InterpretCmd(data *d);

/* helpers2.c */
void _perror(const char *str1, const char *str2);
void _functionTrimage(char *str);
void *_memoryRealloc(void *ptr, unsigned int new_size);

/* exec.c */
void debutDeProcess(data *d);
void signeEviter(int sig);
void Execute(data *d);

/* path.c */
char *_trouveEnv(char *name);
int _functionWich(data *d);
int setenvFunction(data *d, char *name, char *value);

/* string_utils.c */
unsigned int _strlen(char *str);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, int n);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);


/* string_utils2.c */
char *_strdup(const char *str);
int Cnum(const char *status);
int Cdigit(int c);

/* _getline.c */
#define BufferSize 1024

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);


#endif