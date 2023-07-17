#include "shell.h"

/**
 * _realloc - is the function that reallocates a memory using malloc and free
 * @ptr: is the pointer to last allocetd memory
 * @_oldsize: is he size of space for ptr
 * @_newsize: is the new size of ptr
 * Return: return the array wath ever he's realloceted or not or null
 */
void *_realloc(void *ptr, unsigned int _oldsize, unsigned int _newsize)
{
	void *memo;
	char *ptr_copy, *filler;
	unsigned int i;

	if (_newsize == _oldsize)
		return (ptr);

	if (ptr == NULL)
	{
		memo = malloc(_newsize);
		if (memo == NULL)
			return (NULL);

		return (memo);
	}

	if (_newsize == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	memo = malloc(sizeof(*ptr_copy) * _newsize);
	if (memo == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = memo;

	for (i = 0; i < _oldsize && i < _newsize; i++)
		filler[i] = *ptr_copy++;

	free(ptr);
	return (memo);
}

/**
 * assign_buf - is the function that reassigns the buf_ptr variable
 * @buf_ptr: is the buffer to store an input string from the user.
 * @size_bufp: is the size of buf_ptr.
 * @buf: is the string to assign a new value
 * @size_buf: is the size of buf
 */
void assign_buf(char **buf_ptr, size_t *size_bufp, char *buf, size_t size_buf)
{
	if (*buf_ptr == NULL)
	{
		if (size_buf > 120)
			*size_bufp = size_buf;
		else
			*size_bufp = 120;
		*buf_ptr = buf;
	}
	else if (*size_bufp < size_buf)
	{
		if (size_buf > 120)
			*size_bufp = size_buf;
		else
			*size_bufp = 120;
		*buf_ptr = buf;
	}
	else
	{
		_strcpy(*buf_ptr, buf);
		free(buf);
	}
}
