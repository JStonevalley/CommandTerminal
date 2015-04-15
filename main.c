#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

char** tokenizeString(char* command_string, int * num_tokens);

bool route_command(char **command_tokens, int num_tokens);

int main() {
    int nbytes = 100;
    char command_string[nbytes];


    bool exit = false;
    while(!exit){
        char *c = fgets(command_string, nbytes, stdin);
        int num_tokens = 0;
        char **command_tokens = tokenizeString(command_string, &num_tokens);
        exit = route_command(command_tokens, num_tokens);
    }
    return 0;
}

bool route_command(char **command_tokens, int num_tokens){
    char exit_string[] = "exit\n";
    if(!strcmp(command_tokens[0], exit_string)){
        return true;
    }
    return false;
}

char** tokenizeString(char *command_string, int *num_tokens){
    char** return_pointer = NULL;
    int tokens = 0;
    char *token;
    token = strtok(command_string, " ");
    while (token != NULL){
        return_pointer = realloc(return_pointer, sizeof(char*) * (++tokens));
        return_pointer[tokens - 1] = token;
        puts(token);
        token = strtok(NULL, " ");
    }
    *num_tokens = tokens;
    return return_pointer;
}
