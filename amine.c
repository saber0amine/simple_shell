#include "shell2.h"

/**
 * change_directory - function to change the current directory
 * @directory: the folder path
 */
void change_directory(const char *directory)
{
	char cwd[1024];
	if (chdir(directory) == -1)
	{
		perror("chdir");
		return;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return;
	}
	set_env_variable("PWD", cwd);
}

/**
 * env_shell - function to print the current environment
 */
void env_shell(void)
{
	int i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * execute_command - Execute the shell command
 * @command: The command line
 */
void execute_command(char **command)
{
	if (command == NULL || command[0] == NULL)
		return;

	if (strcmp(command[0], "exit") == 0)
	{
		handle_exit(command);
		return;
	}
	else if (strcmp(command[0], "env") == 0)
	{
		env_shell();
		return;
	}
	else if (strcmp(command[0], "setenv") == 0)
	{
		if (set_env_variable(command) == -1)
			fprintf(stderr, "Failed to set environment variable\n");
		return;
	}
	else if (strcmp(command[0], "unsetenv") == 0)
	{
		if (unset_env_variable(command) == -1)
			fprintf(stderr, "Failed to unset environment variable\n");
		return;
	}
	else if (strcmp(command[0], "cd") == 0)
	{
		execute_cd_command(command);
		return;
	}

	pid_t child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		handle_relative_path(command);
		int operator_index = -1;
		for (int i = 0; command[i] != NULL; i++)
		{
			if (strcmp(command[i], "&&") == 0 || strcmp(command[i], "||") == 0)
			{
				operator_index = i;
				break;
			}
		}
		if (operator_index != -1)
		{
			char *operator = command[operator_index];
			command[operator_index] = NULL;
			if (execvp(command[0], command) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (execvp(command[0], command) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		int status;
		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			if (exit_status == 0 && strcmp(command[0], "&&") == 0)
			{
				int i = 0;
				while (command[i] != NULL)
				{
					i++;
				}
				execute_command(&command[i + 1]);
			}
		}
		else
		{
			if (strcmp(command[0], "||") == 0)
			{
				int i = 0;
				while (command[i] != NULL)
				{
					i++;
				}
				execute_command(&command[i + 1]);
			}
		}
	}
}

/**
 * parse_command - Parse the command line into tokens
 * @command_line: The command line to parse
 * Return: An array of tokens
 */
char **parse_command(char *command_line)
{
	char **tokens = NULL;
	char *token = strtok(command_line, " \t\n");
	int num_tokens = 0;

	while (token != NULL)
	{
		tokens = realloc(tokens, sizeof(char *) * (num_tokens + 1));
		if (tokens == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		tokens[num_tokens] = token;
		num_tokens++;
		token = strtok(NULL, " \t\n");
	}
	tokens = realloc(tokens, sizeof(char *) * (num_tokens + 1));
	if (tokens == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	tokens[num_tokens] = NULL;
	return tokens;
}

/**
 * shell_loop - Main loop of the shell
 */
void shell_loop(void)
{
	char *command_line;
	char **command;

	while (1)
	{
		command_line = readline("$ ");
		if (command_line == NULL)
			break;

		add_history(command_line);

		command = parse_command(command_line);

		execute_command(command);

		free(command_line);
		free(command);
	}
}

/**
 * main - Entry point of the shell program
 * @argc: The argument count
 * @argv: The argument vector
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	shell_loop();

	return 0;
}
