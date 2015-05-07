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
    pid_t printenv_pid, sort_pid;
    int status, printenv_sort[2], sort_pager[2];
    if (-1 == pipe(printenv_sort)){
        return false;
    }
    if (-1 == pipe(sort_pager)){
        return false;
    }
    if ((printenv_pid = fork()) == 0) {
        dup2(printenv_sort[WRITE], STDOUT_FILENO);
        close(printenv_sort[READ]);
        close(sort_pager[READ]);
        close(sort_pager[WRITE]);
        if (execlp("printenv", "printenv", NULL) == -1) {
            printf("Failed to start printenv: %s\n", strerror(errno));
            exit(1);
        }
    }
    else {
        if ((sort_pid = fork()) == 0) {
            dup2(printenv_sort[READ], STDIN_FILENO);
            dup2(sort_pager[WRITE], STDOUT_FILENO);
            close(printenv_sort[WRITE]);
            close(sort_pager[READ]);
            if (execlp("sort", "sort", NULL) == -1) {
                printf("Failed to start sort: %s\n", strerror(errno));
                exit(1);
            }
        }
        else {
            if (printenv_pid != 0 && sort_pid != 0) {
                dup2(sort_pager[READ], STDIN_FILENO);
                close(printenv_sort[READ]);
                close(printenv_sort[WRITE]);
                close(sort_pager[WRITE]);
                if (execlp("less", "less", NULL) == -1) {
                    printf("Failed to start pager: %s\n", strerror(errno));
                    exit(1);
                }
            }
        }
    }
    close(printenv_sort[READ]);
    close(printenv_sort[WRITE]);
    close(sort_pager[READ]);
    close(sort_pager[WRITE]);
    wait(&status);
    wait(&status);
    wait(&status);
    return true;
}
