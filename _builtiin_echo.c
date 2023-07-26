#include "shell.h"

/**
 * _itoa - converts an integer to a string
 * @num: integer to be converted
 * Return: pointer to the converted string
 */

char *_itoa(int num)
{
	int i = 0, j = 0, k = 0, l = 0, m = 0;
	char *str = NULL;

	if (num == 0)
	{
		str = malloc(sizeof(char) * 2);
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (num < 0)
		l = 1;
	m = num;
	while (m != 0)
	{
		m /= 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1 + l));
	if (str == NULL)
		return (NULL);
	if (l == 1)
		str[0] = '-';
	for (j = i - 1 + l; j >= l; j--)
	{
		k = num % 10;
		if (k < 0)
			k *= -1;
		str[j] = k + '0';
		num /= 10;
	}
	str[i + l] = '\0';
	return (str);
}

/**
 * handle_echo_args - handles the $ builtin
 * @tokens: array of strings
 * @status: exit status
 */

void handle_echo_args(char *tokens)
{
	char *value = NULL;

	if (tokens == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return;
	}
	if (_strncmp(tokens, "$", 1) == 0)
	{
		value = _getenv(tokens + 1);
		if (value != NULL)
		{
			write(STDOUT_FILENO, value, _strlen(value));
			write(STDOUT_FILENO, "\n", 1);
			return;
		}
	}
	if (_strncmp(tokens, "$$", 2) == 0)
	{
		value = _itoa(getpid());
		write(STDOUT_FILENO, value, _strlen(value));
		write(STDOUT_FILENO, "\n", 1);
		free(value);
		return;
	}
	if (_strncmp(tokens, "$?", 2) == 0)
	{
		write(STDOUT_FILENO, _getenv("?"), _strlen(_getenv("?")));
		write(STDOUT_FILENO, "\n", 1);
		free(value);
		return;
	}
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * handle_echo - handles the echo builtin with '"'
 * @tokens: array of strings
 * @status: exit status
 * Return: 1 if the command is a builtin, 0 if not
 */

int echo_builtin(char **array)
{
	int i = 1, flag = 0, j = 0;

	if (array == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	if (_strncmp(array[0], "echo", 4) != 0)
		return (0);
	if (array[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	if (_strncmp(array[1], "$", 1) == 0 || _strncmp(array[1], "$$", 2) == 0 ||
	    _strncmp(array[1], "$?", 2) == 0)
	{
		handle_echo_args(array[1]);
		return (1);
	}
	for (i = 1; array[i] != NULL; i++)
	{
		for (j = 0; array[i][j] != '\0'; j++)
		{
			if (array[i][j] == '$')
			{
				flag = 1;
				handle_echo_args(array[i] + j);
				break;
			}
			if (array[i][j] != '"')
				write(STDOUT_FILENO, &array[i][j], 1);
		}
		if (array[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}
