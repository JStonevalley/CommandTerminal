#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#include "main.h"
#include "routing.h"
#include "signal_handler.h"

int main() {
	bool exit;
	int nbytes;
	char input[100];
	char *args[10];
	int size;
	bool background = false;

	register_ctrlc_handler();
	#if SIDGET == 1
		register_sig_handler();
	#endif
	
	nbytes = 100;
	exit = false;

	while(!exit){
		#if SIDGET != 1
			poll_background();
		#endif
		input[0] = '\0';
		type_prompt();
		fgets(input, nbytes, stdin);
		tokenize_string(input, args, &size, &background);
		exit = route_command(args, size, background);
	}
	return 0;
}

void type_prompt() {
	char *directory;
	directory = getcwd(NULL, 100);
	printf("%s/ > ", directory);
}

void poll_background() {
	pid_t pid;
	while ((pid = waitpid((pid_t)(-1), 0, WNOHANG)) > 0) {
		printf("[%d] Done!\n", pid);
	}
}
