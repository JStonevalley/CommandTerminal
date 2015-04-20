#include <stdbool.h>
#include <string.h>
#include "routing.h"
#include <stdlib.h>
#include <stdio.h>

bool route_command(struct string_array parameters){
    char exit_string[] = "exit\n";
    if(!strcmp(parameters.array[0], exit_string)){
        return true;
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