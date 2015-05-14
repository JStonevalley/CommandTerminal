#define _XOPEN_SOURCE 500

#include <sys/wait.h>
#include <sys/signal.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "signal_handler.h"

/* register a signal handler that listens SIGCHLD & SIGINT */
void register_sig_handler() {
    struct sigaction sa;
    sa.sa_handler = &sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    sigaction(SIGINT, &sa, 0);
    sigaction(SIGCHLD, &sa, 0);
}

void sig_handler(int sig) {
    pid_t pid;
    
    switch(sig) {
        case SIGINT: /* ignore CTRL+X */
            printf("\n");
            break;
        case SIGCHLD: /* wait for children and print out pid */
            while ((pid = waitpid((pid_t)(-1), 0, WNOHANG)) > 0) {
                printf("[%d] Done!\n", pid);
            }
            break;
    }   
}
