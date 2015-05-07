#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "routing.h"
#include "new_processes.h"
#include "check_env.h"

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
        } else if (!strcmp(first_parameter, "checkEnv")) {
            checkEnv(parameters);
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
    char *prev_token = "";
    
    tokens = 0;
    token = strtok(command_string, " \n");

    while (token != NULL){
        string_tokens = realloc(string_tokens, sizeof(char*) * (++tokens));
        string_tokens[tokens - 1] = token;
        prev_token = token;
        token = strtok(NULL, " \n");
    }

    if (contains_ampersand(prev_token))
    {
        size_t length = strlen(prev_token);
        if (length > 1) /* skip "&" */
        {
            prev_token[length - 1] = '\0';
            string_tokens[tokens - 1] = prev_token;
            /* put a & at the end */
            string_tokens = realloc(string_tokens, sizeof(char*) * (++tokens));
            string_tokens[tokens - 1] = "&";
        }
    }

    string_tokens = realloc(string_tokens, sizeof(char*) * (tokens + 1));
    string_tokens[tokens] = NULL;

    array.size = tokens;
    array.array = string_tokens;
    return array;
}

bool contains_ampersand(char *string) {
    int length = strlen(string);
    int i;

    for (i = 0; i < length; ++i)
    {
        if (string[i] == '&' && string[i+1] == '\0')
        {
            return true;
        }
    }
    return false;
}
