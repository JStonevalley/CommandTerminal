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
    struct string_array tokens;

    register_sig_handler();

    nbytes = 100;
    exit = false;
    while(!exit){
        type_prompt();
        fgets(command_string, nbytes, stdin);
        tokens = tokenizeString(command_string);
        exit = route_command(tokens);
    }
    return 0;
}

void type_prompt() {
    char *directory;
    directory = getcwd(NULL, 100);
    printf("%s/ > ", directory);
}
