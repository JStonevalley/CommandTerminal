#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "new_processes.h"

void foreground_process(char *file, char **args){
    pid_t pid;
    int status;
    struct timeval  tv1, tv2;

    if ((pid = fork()) == 0) {
        /*  In child process */
        if (execvp(file, args) == -1) {
            printf("Failed to start: %s\n", strerror(errno));
            exit(1); /* Kill confused child! */
        }
    } else {
        /* In parent process */
        gettimeofday(&tv1, NULL); /* mark start time */
        waitpid(pid, &status, 0);
        gettimeofday(&tv2, NULL); /* mark end time */

        printf ("Total time = %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));
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
