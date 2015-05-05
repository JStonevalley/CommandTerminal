#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/times.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include "new_processes.h"

void foreground_process(char *file, char **args){
    pid_t pid;
    int status;
    struct timespec start, end;
    uint64_t diff;

    if ((pid = fork()) == 0) {
        /*  In child process */
        if (execvp(file, args) == -1) {
            printf("Failed to start: %s\n", strerror(errno));
            exit(1); /* Kill confused child! */
        }
    } else {
        /* In parent process */
        clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
        waitpid(pid, &status, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);   /* mark the end time */
        diff = end.tv_sec - start.tv_sec;

        printf("Execution time was %f seconds for PID %d\n", ((double) time.tms_utime)/tics_per_second, pid);            

    }
}

void background_process(char *file, char **args){
    pid_t pid;
    /* int status; */

    if ((pid = fork()) == 0) {
        /* In child process */
        if (execvp(file, args) == -1) {
            printf("Failed to start: %s\n", strerror(errno));
            exit(1);
        }
        exit(0);
    } else {
        /* Lalalalalala */
    }
}
