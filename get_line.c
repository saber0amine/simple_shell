#include "shell.h"

/**
 * _getline - is the function that take str from input and put it on buffer
 * @bufferptr: is thebuffer to store the input
 * @buf_size: is the size of bufferptr
 * @stream: is the stream to read from
 * Return: return the number of bytes read
 */
ssize_t _getline(char **bufferptr, size_t *buf_size, FILE *stream)
{
	static ssize_t input;
	ssize_t n_chars;
	char c = 'x', *buffer;
	int reaad;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;
	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);
	while (c != '\n')
	{
		reaad = read(STDIN_FILENO, &c, 1);
		if (reaad == -1 || (reaad == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (reaad == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';
	assign_buf(bufferptr, buf_size, buffer, input);
	n_chars = input;
	if (reaad != 0)
		input = 0;
	return (n_chars);
}
