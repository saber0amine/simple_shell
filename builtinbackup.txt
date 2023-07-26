#include "shell.h"

/**
 * change_dir - is the function for change dir
 * @target_dir: is the directory to go for it
 */

void change_dir(char *target_dir)
{
	char *pwd = getcwd(NULL, 0);
	char error_msg[100];
	const char *prefix = "./hsh: 1: cd: can't cd to ";
	int i, j;
	const char *suffix = "\n";

	if (pwd == NULL)
	{
		perror("getwcd");
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

/**
 * cd_builtin - is the function that change the current working dir
 * @array: is the array where is stored the data
 */

void cd_builtin(char **array)
{
	char *target_dir = NULL, *oldpwd = NULL;

	if (array[1] == NULL)
	{
		target_dir = _getenv("HOME");
	}
	else if (strcmp(array[1], "-") == 0)
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
		target_dir = array[1];
	}

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		perror("getcwd");
		return;
	}
	change_dir(target_dir);
	/*if (strcmp(array[1], "-") == 0)
	{
		printf("%s\n", target_dir);
	}*/
	free(oldpwd);
}
