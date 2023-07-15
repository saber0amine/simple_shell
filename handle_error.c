#include "shell.h"
/**
 * handle_error - a function to handle error
 */
void handle_error(void)
{
perror("Error");
exit(EXIT_FAILURE);
}