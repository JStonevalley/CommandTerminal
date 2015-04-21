#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "new_processes.h"

void foreground_process(char *file, char **args){
    pid_t pid;
    int status;

    if ((pid = fork()) == 0) {
        if (execvp(file, args) == -1) {
            printf("Failed to start: %s\n", strerror(errno));
        }
    }
    waitpid(pid, &status, 0);
}

void background_process(char *file, char **args){
    pid_t pid;
    int status;

    if ((pid = fork()) == 0) {
        if (execvp(file, args) == -1) {
            printf("Failed to start: %s\n", strerror(errno));
        }
    }
}