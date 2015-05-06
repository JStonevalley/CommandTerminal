#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "main.h"
#include "routing.h"
#include "signal_handler.h"

int main() {
    bool exit;
    int nbytes;
    char command_string[100];
    char *c;
    struct string_array tokens;

    register_sig_handler();

    nbytes = 100;
    exit = false;
    while(!exit){
        c = getcwd(command_string, 100);
        printf("%s/ ", c);
        printf("> ");
        c = fgets(command_string, nbytes, stdin);
        tokens = tokenizeString(command_string);
        exit = route_command(tokens);
    }
    return 0;
}
