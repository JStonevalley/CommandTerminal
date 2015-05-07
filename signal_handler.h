#ifndef COMMANDTERMINAL_SIGNAL_HANDLER_H
#define COMMANDTERMINAL_SIGNAL_HANDLER_H

#endif

void register_sig_handler();
void register_ctrlc_handler();
void handle_sigchld(int sig);
void handle_ctrlc(int sig);
