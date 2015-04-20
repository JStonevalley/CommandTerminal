#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <dirent.h>
#include "main.h"
#include "routing.h"

int main() {
    DIR *current_location;
    bool exit;
    int nbytes;
    char command_string[100];
    char *c;
    struct string_array tokens;
    current_location = opendir(".");
    nbytes = 100;
    exit = false;
    while(!exit){
        putc('>', stdout);
        c = fgets(command_string, nbytes, stdin);
        tokens = tokenizeString(command_string);
        exit = route_command(tokens, current_location);
    }
    return 0;
}
