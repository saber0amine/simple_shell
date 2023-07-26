#include "main.h"

void change_dir(char *target_dir)
{
	char *pwd = getcwd(NULL, 0);
	char error_msg[100];
	const char *prefix = "./hsh: 1: cd: can't cd to ";
	int i, j;
	const char *suffix = "\n";

	if (pwd == NULL)
	{
		perror("getcwd");
		return;
	}
	if (chdir(target_dir) == -1)
	{
		for (i = 0; prefix[i] != '\0'; i++)
			error_msg[i] = prefix[i];
		for (j = 0; target_dir[j] != '\0'; j++, i++)
			error_msg[i] = target_dir[j];
		for (j = 0; suffix[j] != '\0'; j++, i++)
			error_msg[i] = suffix[j];
		error_msg[i] = '\0';
		write(STDERR_FILENO, error_msg, i);
		free(pwd);
		return;
	}
	if (setenv("PWD", target_dir, 1) != 0)
	{
		perror("setenv");
		free(pwd);
		return;
	}
	if (setenv("OLDPWD", pwd, 1) != 0)
	{
		perror("setenv");
	}

	free(pwd);
}	

void builtin_cd(data *d)
{
	char *target_dir = NULL, *oldpwd = NULL;

	if (d->av[1] == NULL)
	{
		target_dir = _getenv("HOME");
	}
	else if (strcmp(d->av[1], "-") == 0)
	{
		target_dir = _getenv("OLDPWD");
		if (target_dir == NULL)
		{
			write(STDERR_FILENO, "OLDPWD not set\n", 14);
			return;
		}
	}
	else
	{
		target_dir = d->av[1];
	}

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		perror("getcwd");
		return;
	}
	change_dir(target_dir);
	if (d->av[1] != NULL && strcmp(d->av[1], "-") == 0)
	{
		write(STDOUT_FILENO, target_dir, strlen(target_dir));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(oldpwd);
}
