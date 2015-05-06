#include <sys/signal.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "signal_handler.h"

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

void handle_sigchld(int sig) {
    pid_t pid;
    while ((pid = waitpid((pid_t)(-1), 0, WNOHANG)) > 0) {
        printf("[%d] Done!\n", pid);
    }
}
