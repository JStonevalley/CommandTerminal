#define _XOPEN_SOURCE 500

#include <sys/wait.h>
#include <sys/signal.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "signal_handler.h"

/* register a signal handler that listens to signals from children */
void register_sig_handler() {
    struct sigaction sa;
    sa.sa_handler = &handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    if (sigaction(SIGCHLD, &sa, 0) == -1) {
        perror(0);
        exit(1);
    }
}

/* register a signal handler that listens to interuption signals (CTRL+C) */
void register_ctrlc_handler() {
    struct sigaction sa;
    sa.sa_handler = &handle_ctrlc;
    sigaction(SIGINT, &sa, NULL);
}

/* wait for children and print out pid */
void handle_sigchld(int sig) {
    pid_t pid;
    while ((pid = waitpid((pid_t)(-1), 0, WNOHANG)) > 0) {
        printf("[%d] Done!\n", pid);
    }
}

void handle_ctrlc(int sig) {
    printf("\n");
}
