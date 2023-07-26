#include "shell.h"

/**
 * change_dir - is the function for change dir
 * @target_dir: is the directory to go for it
 */

void change_dir(char *target_dir)
{
	char *pwd = getcwd(NULL, 0);

	if (pwd == NULL)
	{
		perror("getwcd");
		return;
	}

	if (chdir(target_dir) == -1)
	{
		perror("chdir");
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
	free(oldpwd);
}
