#include "main.h"

/**
 * _getline_helper - is the function that give the size to getline
 * @strline: is the string input
 * @n: is the size of the string
 * Return: int
 */
int _getline_helper(char **strline, size_t *n)
{
	if (*strline == NULL || *n == 0)
	{
		*n = 128;
		*strline = malloc(*n);
		if (*strline == NULL)
			return (-1);
	}
	return (0);
}

/**
 * _getline - is the funtion that reads the input of the user
 * @strline: is the string input
 * @n: isthe size of the string
 * @stream: FILE input
 * Return: ssize_t
 */
ssize_t _getline(char **strline, size_t *n, FILE *stream)
{
	ssize_t _nbytes = 0;
	size_t position = 0, size;
	static char buffer[READ_BUF_SIZE];
	static size_t buffersize, bufferpos;
	char *newbuffer;

	if (strline == NULL || n == NULL || stream == NULL
		|| _getline_helper(strline, n) == -1)
		return (-1);
	while (1)
	{
		if (bufferpos >= buffersize)
		{
			_nbytes = read(stream->_fileno, buffer, READ_BUF_SIZE);
			if (_nbytes <= 0 && position == 0)
				return (-1);
			else if (_nbytes <= 0)
				break;
			buffersize = _nbytes;
			bufferpos = 0;
		}
		if (position >= *n - 1)
		{
			size = *n * 2;
			newbuffer = realloc(*strline, size);
			if (newbuffer == NULL)
				return (-1);
			*strline = newbuffer;
			*n = size;
		}
		(*strline)[position++] = buffer[bufferpos++];
		if ((*strline)[position - 1] == '\n')
			break;
	}
	(*strline)[position] = '\0';
	return (position);
}
