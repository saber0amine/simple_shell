#include "shell.h"

/**
 * _getline_checker - is the function that check if nothing on the bufferptr
 * @bufferptr: string input
 * @buf_size: is the size of the buffer
 * Return: 0 if all is good or -1 if not
 */
int _getline_checker(char **bufferptr, size_t *buf_size)
{
	if (*bufferptr == NULL || *buf_size == 0)
	{
		*buf_size = 128;
		*bufferptr = malloc(*buf_size);
		if (*bufferptr == NULL)
			return (-1);
	}
	return (0);
}

/**
 * _getline - the function that reads the input from FILE
 * @bufferptr: string input
 * @buf_size: buffer size
 * @stream: FILE input
 * Return: the position of the buffer
 */
ssize_t _getline(char **bufferptr, size_t *buf_size, FILE *stream)
{
	static size_t bufsize, bufposition;
	static char buf[READ_BUF_SIZE];
	ssize_t readbytes = 0;
	size_t position = 0, newsize;
	char *newbuffer;

	if (bufferptr == NULL || buf_size == NULL || stream == NULL
		|| _getline_checker(bufferptr, buf_size) == -1)
		return (-1);
	while (1)
	{
		if (bufposition >= bufsize)
		{
			readbytes = read(stream->_fileno, buf, READ_BUF_SIZE);
			if (readbytes <= 0 && position == 0)
				return (-1);
			else if (readbytes <= 0)
				break;
			bufsize = readbytes;
			bufposition = 0;
		}
		if (position >= *buf_size - 1)
		{
			newsize = *buf_size * 2;
			newbuffer = realloc(*bufferptr, newsize);
			if (newbuffer == NULL)
				return (-1);
			*bufferptr = newbuffer;
			*buf_size = newsize;
		}
		(*bufferptr)[position++] = buf[bufposition++];
		if ((*bufferptr)[position - 1] == '\n')
			break;
	}
	(*bufferptr)[position] = '\0';
	return (position);
}
