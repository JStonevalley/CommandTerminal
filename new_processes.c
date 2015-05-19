#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "new_processes.h"

/*
	Starts a new process in the foreground, i.e peel waits for it to finish.
	Measure the time taken from start to finish and prints it to stdout.
*/
void foreground_process(char *file, char **args){
    pid_t pid;
    int status;
    struct timeval tv1, tv2;

    if ((pid = fork()) == 0) {
        /*  In child process */
        if (execvp(file, args) == -1) {
            printf("Failed to start: %s\n", strerror(errno));
            exit(1); /* Kill confused child! */
        }
    } else {
        /* In parent process */
        gettimeofday(&tv1, NULL); /* mark start time */
        if(waitpid(pid, &status, 0) == -1)
            fprintf(stderr, "Error waiting: %d\n", errno);
        gettimeofday(&tv2, NULL); /* mark end time */

        printf ("Total time = %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));
    }
}

/*
	Starts a new process in the background, i.e peel does not wait for it to finish.
	Sets a signal mask on the child to ignore SIGINT (CTRL+C).
*/
void background_process(char *file, char **args){
    pid_t pid;

    if ((pid = fork()) == 0) {
        sighold(SIGINT); /* don't exit on CTRL+C */
        /* In child process */
        if (execvp(file, args) == -1) {
            printf("Failed to start: %s\n", strerror(errno));
            exit(1);
        }
        exit(0);
    }
}
