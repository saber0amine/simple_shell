#include "shell.h"





char* replace_variable(const char* input, const char* variable, const char* value) {
    const char* found = strstr(input, variable);
    if (found == NULL) {
        return strdup(input);
    }

    size_t variable_length = strlen(variable);
    size_t value_length = strlen(value);
    size_t input_length = strlen(input);
    size_t result_length = input_length - variable_length + value_length + 1;

    char* result = malloc(result_length);
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memcpy(result, input, found - input);
    memcpy(result + (found - input), value, value_length);
    memcpy(result + (found - input) + value_length, found + variable_length, input_length - (found - input) - variable_length + 1);

    return result;
}