#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "check_env.h"

int pipes[7];

bool checkEnv(struct string_array parameters){
    pid_t printenv_pid, sort_pid;
    int status;
    if (parameters.size > 0){
        initiate_pipes(3);
    }
    else{
        initiate_pipes(2);
    }
    if ((printenv_pid = fork()) == 0) {
        printenv(&pipes[0]);
    }
    else {
        if ((sort_pid = fork()) == 0) {
            sort(&pipes[0], &pipes[2]);
        }
        else {
            if (printenv_pid != 0 && sort_pid != 0) {
               pager(&pipes[2]);
            }
        }
    }
    close_pipes();
    wait(&status);
    wait(&status);
    return true;
}

void printenv(int outpipe[2]){
    dup2(outpipe[WRITE], STDOUT_FILENO);
    close_pipes();
    if (execlp("printenv", "printenv", NULL) == -1) {
        printf("Failed to start printenv: %s\n", strerror(errno));
        exit(1);
    }
}

void sort(int inpipe[2], int outpipe[2]){
    dup2(inpipe[READ], STDIN_FILENO);
    dup2(outpipe[WRITE], STDOUT_FILENO);
    close_pipes();
    if (execlp("sort", "sort", NULL) == -1) {
        printf("Failed to start sort: %s\n", strerror(errno));
        exit(1);
    }
}

void pager(int inpipe[2]){
    dup2(inpipe[READ], STDIN_FILENO);
    close_pipes();
    if (execlp("less", "less", NULL) == -1) {
        printf("Failed to start pager: %s\n", strerror(errno));
        exit(1);
    }
}

void close_pipes(){
    int i = 0;
    int temp_pipe = pipes[i];
    while (temp_pipe != -1){
        close(temp_pipe);
        temp_pipe = pipes[++i];
    }
}

void initiate_pipes(int number_of_pipes) {

    if (-1 == pipe(pipes)){
        pipes[0] = -1;
        pipes[1] = -1;
    }
    if (-1 == pipe(pipes + 2)){
        pipes[2] = -1;
        pipes[3] = -1;
    }
    if (number_of_pipes == 3){
        if (-1 == pipe(pipes + 4)){
            pipes[4] = -1;
            pipes[5] = -1;
        }
    }
    else{
        pipes[4] = -1;
        pipes[5] = -1;
    }
    pipes[6] = -1;
}


