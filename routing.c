#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "routing.h"

bool route_command(struct string_array parameters, char **current_direction){
    if (parameters.size > 0) {
        if (!strcmp(parameters.array[0], "exit\n") || !strcmp(parameters.array[0], "exit")) {
            return true;
        }
        else if (!strcmp(parameters.array[0], "cd")) {
            parameters.array++;
            parameters.size--;
            cd(parameters, current_direction);
        }
        else if (!strcmp(parameters.array[0], "ls\n")) {
            parameters.array++;
            parameters.size--;
            ls(parameters, current_direction);
        }
    }
    return false;
}

struct string_array tokenizeString(char *command_string){
    char **string_tokens = NULL;
    struct string_array array;
    int tokens;
    char *token;
    tokens = 0;
    token = strtok(command_string, " ");
    while (token != NULL){
        string_tokens = realloc(string_tokens, sizeof(char*) * (++tokens));
        string_tokens[tokens - 1] = token;
        puts(token);
        token = strtok(NULL, " ");
    }

    array.size = tokens;
    array.array = string_tokens;
    return array;
}