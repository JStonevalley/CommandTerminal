#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "main.h"
#include "routing.h"

int main() {
    char *current_location;
    bool exit;
    int nbytes;
    char command_string[100];
    char *c;
    struct string_array tokens;

    current_location = ".";
    nbytes = 100;
    exit = false;
    while(!exit){
        c = getcwd(command_string, 100);
        printf("%s/ ", c);
        printf("> ");
        c = fgets(command_string, nbytes, stdin);
        tokens = tokenizeString(command_string);
        exit = route_command(tokens, &current_location);
    }
    return 0;
}
