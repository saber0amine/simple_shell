<<<<<<< HEAD
#include "shell.h"

/*
* my_strtok ; implementation of our strtok function
* @str: str
* @delim: delimiter
* Return: return the next token in the string
*/

char* my_strtok(char* str, const char* delim) 
{
static char* state = NULL;
char* token;
if (str == NULL && state == NULL)
{
return NULL;
}
if (str != NULL)
{
state = str;
}
token = state;
char* delim_ptr = strpbrk(state, delim);
if (delim_ptr == NULL)
{
state = NULL;
} 
else
{
*delim_ptr = '\0';
state = delim_ptr + 1;
}
return token;
}
=======
#include "shell.h"


char* my_strtok(char* str, const char* delim) 
{
static char* state = NULL;
char* token;
if (str == NULL && state == NULL) {
        return NULL;
    }

    if (str != NULL) {
        state = str;
    }

    token = state;

    char* delim_ptr = strpbrk(state, delim);

    if (delim_ptr == NULL) {
        state = NULL;
    } else {
        *delim_ptr = '\0';
        state = delim_ptr + 1;
    }

    return token;
}


>>>>>>> master
