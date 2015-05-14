#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "main.h"
#include "routing.h"
#include "signal_handler.h"

int main() {
    bool exit;
    int nbytes;
    char input[100];
    char *args[10];
    int size = 0;
    bool background = false;

    register_sig_handler();

    nbytes = 100;
    exit = false;
    
    while(!exit){
        type_prompt();
        fgets(input, nbytes, stdin);
        tokenize_string(input, args, &size, &background);
        exit = route_command(args, size, background);
    }
    return 0;
}

void type_prompt() {
    char *directory;
    directory = getcwd(NULL, 100);
    printf("%s/ > ", directory);
}
