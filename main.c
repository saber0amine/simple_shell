#include "main.h"

/**
 * main - is the main function that lance the program
 * @argc: is number of @argv
 * @argv: is an array of arguments
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	data d;
	(void)argc;
	initial_data(&d, argv[0]);
	_execmd(&d);

	return (0);
}
