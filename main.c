#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "main.h"
#include "routing.h"

int main() {
    bool exit;
    int nbytes;
    char command_string[100];
    char *c;
    struct string_array tokens;

    nbytes = 100;
    exit = false;
    while(!exit){
        c = getcwd(command_string, 100);
        printf("%s/ ", c);
        printf("> ");
        c = fgets(command_string, nbytes, stdin);
        tokens = tokenizeString(command_string);
        puts(tokens.array[0]);
        printf("%d\n", tokens.size);
        exit = route_command(tokens);
        printf(exit ? "true\n" : "false\n");

    }
    return 0;
}
