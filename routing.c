#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "routing.h"
#include "new_processes.h"
#include "check_env.h"

/*
    Given a number of arguments route_command executes the correct process.
*/
bool route_command(char *args[], int size, bool background){
    bool exit;
    char *first_arg;
    exit = false;

    if (size > 0){
        first_arg = args[0];
        if (!strcmp(first_arg, "exit")) {
            exit = true;
        } else if (!strcmp(first_arg, "cd")) {
            cd(args[1]);
        } else if (!strcmp(first_arg, "checkEnv")) {
            checkEnv(args, size);
        } else if (background) {
            background_process(first_arg, args);
        } else {
            foreground_process(first_arg, args);
        }
    }
    return exit;
}

/*
    Splits the input into a series of arguments. The number of arguments are put
    int the variable size and the boolean background is returned as true iff
    the input ends with an ampersand (&).
*/
void tokenize_string(char* input, char *args[], int *size, bool *background) {
    char *arg;
    *size = 0;

    arg = strtok(input, " \n");
    while (arg != NULL) {
    	args[*size] = arg;
        arg = strtok(NULL, " \n");
        (*size)++;
    }

    if (*size > 0) {
        *background = contains_ampersand(args, *size);
    }
    args[*size] = NULL; /* null terminate array */
}

/*
    Finds and sanetized the arguments from ampersand (&). 
	Returns true iff it finds an amptersant (&).
*/
bool contains_ampersand(char *args[], int size) {
    char *lastArg = args[size - 1];
    int stringLength = strlen(lastArg);
    int i;

    for (i = 0; i < stringLength; ++i) {
        if (lastArg[i] == '&' && lastArg[i+1] == '\0') {
            if (stringLength == 1)
                args[size - 1] = NULL;
            else
                lastArg[i] = '\0';

            return true;
        }
    }
    return false;
}
