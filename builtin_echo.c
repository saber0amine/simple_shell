#include "main.h"

/**
 * _inttostr - is the function that conver from int to string
 * @num: is the int we want to convert
 * Return: return the string
 */

char *_inttostr(int num)
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
 * echo_args - is the function that handel $
 * @tokens: is a string
 * @status: is the exit status
 */

void echo_args(char *tokens, int status)
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
		value = _inttostr(getpid());
		write(STDOUT_FILENO, value, _strlen(value));
		write(STDOUT_FILENO, "\n", 1);
		free(value);
		return;
	}
	if (_strncmp(tokens, "$?", 2) == 0)
	{
		value = _inttostr(status);
		write(STDOUT_FILENO, value, _strlen(value));
		write(STDOUT_FILENO, "\n", 1);
		free(value);
		return;
	}
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * echo_builtin - is the function that builtin echo
 * @d: is the data
 */

void echo_builtin(data *d)
{
	int i = 1, flag = 0, j = 0;

	if (d->av[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return;
	}
	if (_strncmp(d->av[0], "echo", 4) != 0)
		return;
	for (i = 1; d->av[i] != NULL; i++)
	{
		if (_strncmp(d->av[1], "$", 1) == 0 || _strncmp(d->av[1], "$$", 2) == 0
				|| _strncmp(d->av[1], "$?", 2) == 0)
		{
			echo_args(d->av[1], d->last_exit_status);
			return;
		}
		for (i = 1; d->av[i] != NULL; i++)
		{
			for (j = 0; d->av[i][j] != '\0'; j++)
			{
				if (d->av[i][j] == '$')
				{
					flag = 1;
					echo_args(d->av[i] + j, d->last_exit_status);
					break;
				}
				if (d->av[i][j] != '"')
					write(STDOUT_FILENO, &d->av[i][j], 1);
			}
			if (d->av[i + 1] != NULL)
				write(STDOUT_FILENO, " ", 1);
		}
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
}
