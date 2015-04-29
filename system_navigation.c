#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "system_navigation.h"

void cd(struct string_array parameters) {
    if (parameters.size > 0) {
        if (chdir(parameters.array[0]) == -1) {
            printf("Directory change failed: %s\n", strerror(errno));
        }
    }
}

void ls(struct string_array parameters, char **current_dir){
    char working_directory[100];
    char *c;
    DIR *d;
    struct dirent *directory;

    c = getcwd(working_directory, 100);
    d = opendir(c);
    if(d){
        while((directory = readdir(d)) != NULL){
            printf("%s\n", directory->d_name);
        }
    }
    closedir(d);
}
