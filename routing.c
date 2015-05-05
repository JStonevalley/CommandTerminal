#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "routing.h"
#include "new_processes.h"

bool route_command(struct string_array parameters){
    char *first_parameter;
    bool exit;
    exit = false;

    if (parameters.size > 0){
        first_parameter = parameters.array[0];
        if (!strcmp(first_parameter, "exit")) {
            exit = true;
        } else if (!strcmp(first_parameter, "cd")) {
            parameters.array++;
            parameters.size--;
            cd(parameters);
        } else if (parameters.array[parameters.size - 1][strlen(parameters.array[parameters.size - 1]) - 1] == '&') {
            parameters.array[parameters.size - 1] = NULL;
            parameters.size--;
            background_process(first_parameter, parameters.array);
        } else {
            foreground_process(first_parameter, parameters.array);
        }
    }
    
    return exit;
}

struct string_array tokenizeString(char *command_string){
    char **string_tokens = NULL;
    struct string_array array;
    int tokens;
    char *token;
    tokens = 0;
    token = strtok(command_string, " \n");

    while (token != NULL){
        string_tokens = realloc(string_tokens, sizeof(char*) * (++tokens));
        string_tokens[tokens - 1] = token;
        token = strtok(NULL, " \n");
    }

    string_tokens = realloc(string_tokens, sizeof(char*) * (tokens + 1));
    string_tokens[tokens] = NULL;

    array.size = tokens;
    array.array = string_tokens;
    return array;
}
