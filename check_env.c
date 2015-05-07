#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "check_env.h"

bool checkEnv(){
    pid_t printenv_pid;
    int pipa[2];
    if (-1 == pipe(pipa)){
        return false;
    }
    printf("pipa[READ] = %d pipa[WRITE] = %d\n", pipa[READ], pipa[WRITE]);
    if ((printenv_pid = fork()) == 0) {
        dup2(pipa[WRITE], STDOUT_FILENO);
        close(pipa[READ]);
        if (execlp("printenv", "printenv", NULL) == -1) {
            printf("Failed to start printenv: %s\n", strerror(errno));
            exit(1);
        }
    }
    else{
        dup2(pipa[READ], STDIN_FILENO);
        close(pipa[WRITE]);
        if (execlp("sort", "sort", NULL) == -1) {
            printf("Failed to start sort: %s\n", strerror(errno));
            exit(1);
        }
    }
    return true;
}
