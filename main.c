#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

char** tokenizeString(char* command_string, int * num_tokens);

int main() {
    int nbytes = 100;
    char command_string[nbytes];
    char exit_string[] = "exit\n";

    bool exit = false;
    while(!exit){
        char *c = fgets(command_string, nbytes, stdin);
        int *num_tokens;
        char **command_tokens = tokenizeString(command_string, num_tokens);
        if(!strcmp(command_tokens[0], exit_string)){
            exit = true;
        }
    }
    return 0;
}

char** tokenizeString(char* command_string, int * num_tokens){
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
