#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
/*
* getinput: implementation of our geline function
* @buffer: buffer
* @size_buf: size of buffer
* @file: file
* return: return the input string
*/
int getinput(char *buffer, int size_buf, FILE *file)
{
    int NbOf_caracters;
    NbOf_caracters = read(fileno(file), buffer, size_buf * sizeof(char));
    if (NbOf_caracters == -1)
    {
        perror("Error reading from file descriptor");
        return -1;
    }
    buffer = realloc(buffer, (NbOf_caracters + 1) * sizeof(char));
    if (buffer == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }
    buffer[NbOf_caracters] = '\0'; // Null-terminate the string

    return (NbOf_caracters -1 );
}

<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
