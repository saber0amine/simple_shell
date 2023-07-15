#include "shell.h"


char* my_strtok(char* str, const char* delim) {
    static char* state = NULL;
    static char* last_token = NULL;

    char* token;

    if (str != NULL) {
        state = str;
        last_token = NULL;
    } else if (state == NULL) {
        return NULL;
    }

    // Skip leading delimiter characters
    while (*state != '\0' && strchr(delim, *state) != NULL) {
        state++;
    }

    // If end of string reached, return NULL
    if (*state == '\0') {
        state = NULL;
        return NULL;
    }

    token = state;

    // Find next delimiter or end of string
    while (*state != '\0' && strchr(delim, *state) == NULL) {
        state++;
    }

    if (*state != '\0') {
        *state = '\0';  // Replace delimiter with null character
        state++;       // Move state to next character after delimiter
    } else {
        last_token = state;
    }

    return token;
}

void env_shell(void) {
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
}



void handle_exit(char **args)
{
int status = 0;
if (args[1] != NULL) {
status = atoi(args[1]);
}
exit(status);
}






char* replace_variable(const char* input, const char* variable, const char* value)
{
const char* found = strstr(input, variable);
if (found == NULL)
{
return strdup(input);
}
size_t variable_length = strlen(variable);
size_t value_length = strlen(value);
size_t input_length = strlen(input);
size_t result_length = input_length - variable_length + value_length + 1;
char* result = malloc(result_length);
if (result == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
memcpy(result, input, found - input);
memcpy(result + (found - input), value, value_length);
memcpy(result + (found - input) + value_length, found + variable_length, input_length - (found - input) - variable_length + 1);
return result;
}



void handle_variable_replacement(char **command, int status)
{
int i = 0;
while (command[i] != NULL)
{
if (strcmp(command[i], "$?") == 0) {
char exit_status[10];
sprintf(exit_status, "%d", WEXITSTATUS(status));
free(command[i]);
command[i] = strdup(exit_status);
}
else if (strcmp(command[i], "$$") == 0) {
char shell_pid[10];
sprintf(shell_pid, "%d", getpid());
free(command[i]);
command[i] = strdup(shell_pid);
}
else if (strstr(command[i], "$")) {
char* variable = strchr(command[i], '$');
char* value = getenv(variable + 1);
if (value != NULL)
{
char* replaced = replace_variable(command[i], variable, value);
free(command[i]);
command[i] = replaced;
}
}
i++;
}
}

void execute_command(char **command) {
if (command == NULL || command[0] == NULL) {
return;
}
if (strcmp(command[0], "exit") == 0) {
handle_exit(command);
return;
}
else if (strcmp(command[0], "env") == 0) {
env_shell();
return;
}
pid_t child_pid = fork();
if (child_pid == -1) {
perror("fork");
exit(EXIT_FAILURE);
}
if (child_pid == 0) {
handle_relative_path(command);
int operator_index = -1;
for (int i = 0; command[i] != NULL; i++) {
if (strcmp(command[i], "&&") == 0 || strcmp(command[i], "||") == 0) {
operator_index = i;
break;
}
}
if (operator_index != -1) {
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
if (execvp(command[0], command) == -1) {
perror("execvp");
exit(EXIT_FAILURE);
}
}
}
else
{
int status;
if (waitpid(child_pid, &status, 0) == -1) {
perror("waitpid");
exit(EXIT_FAILURE);
}
if (WIFEXITED(status)) {
int exit_status = WEXITSTATUS(status);
if (exit_status == 0 && strcmp(command[0], "&&") == 0) {
int i = 0;
 while (command[i] != NULL) {
i++;
}
execute_command(&command[i + 1]);
}
}
else
{
if (strcmp(command[0], "||") == 0) {
int i = 0;
while (command[i] != NULL) {
i++;
}
execute_command(&command[i + 1]);
}
}
}
}   














void exit_shell(void) {
    exit(EXIT_SUCCESS);
}

void handle_error(void) {
    perror("Error");
    exit(EXIT_FAILURE);
}

void handle_relative_path(char **args) {
    if (args[0][0] != '/') {
        char *cmd_path = malloc(strlen(args[0]) + 6);
        if (cmd_path == NULL) {
            fprintf(stderr, "Error: failed to allocate memory\n");
            exit(EXIT_FAILURE);
        }
        sprintf(cmd_path, "/bin/%s", args[0]);
        free(args[0]);
        args[0] = cmd_path;
    }
}

void prompt(void) {
    printf("#cisfun$ ");
}

void read_command(char (*command)[1024]) {
    size_t len;
    if (fgets(*command, 1024, stdin) == NULL) {
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            fprintf(stderr, "Error: failed to read command\n");
            exit(EXIT_FAILURE);
        }
    }
    len = strlen(*command);

    if ((*command)[len - 1] == '\n') {
        (*command)[len - 1] = '\0';
    }
}

void tokenize_command(char *buffer, char **args) {
    char *token;
    int i = 0;

    token = my_strtok(buffer, " \n");
    while (token != NULL) {
        if (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0) {
            // Handle && and || as separate arguments
            args[i++] = token;
        } else {
            args[i++] = strdup(token);
        }
        token = my_strtok(NULL, " \n");
    }
    args[i] = NULL;
}

int getinput(char *buffer, int size_buf, FILE *file)
{
int NbOf_caracters;
NbOf_caracters = read(fileno(file), buffer, size_buf * sizeof(char));
if (NbOf_caracters == -1)
{
perror("Error reading from file descriptor");
return -1;
}
char* temp_buffer = realloc(buffer, (NbOf_caracters + 1) * sizeof(char));
if (temp_buffer == NULL)
{
printf("Memory allocation failed.\n");
return -1;
}
buffer = temp_buffer;
buffer[NbOf_caracters] = '\0';
return (NbOf_caracters - 1);
}

char **parse_command(char *command) {
    char *buffer = strdup(command);
    char **args = malloc(sizeof(char *) * 1024);
    if (args == NULL) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    int arg_index = 0;
    char *token = my_strtok(buffer, " \n");
    while (token != NULL) {
        if (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0) {
            // Handle && and || as separate arguments
            args[arg_index++] = strdup(token);
        } else {
            args[arg_index++] = strdup(token);
        } 
        token = my_strtok(NULL, " \n");
    }
    args[arg_index] = NULL;
    free(buffer);

    return args;
}

int main(void) {
    char command[1024];
    char **parsed_command;
    while (1) {
        prompt();
        read_command(&command);
        parsed_command = parse_command(command);
        if (parsed_command[0] != NULL) {
            execute_command(parsed_command);
        }
    }
    return 0;
}
