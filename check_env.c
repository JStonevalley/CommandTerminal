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
    pid_t printenv_pid, grep_pid, sort_pid, pager_pid;
    int status, read_pipe, write_pipe;
    read_pipe = -2,
    write_pipe = 0;
    if (parameters.size > 1){
        initiate_pipes(3);
        puts(parameters.array[0]);
        puts(parameters.array[1]);
    }
    else{
        initiate_pipes(2);
    }

    if ((printenv_pid = fork()) == 0) {
        printenv(&pipes[write_pipe]);
    }

    if(parameters.size > 1) {
    	increment_pipes(&read_pipe, &write_pipe);

    	if ((grep_pid = fork()) == 0) {
			grep(&pipes[read_pipe], &pipes[write_pipe], parameters.array);
		}
	}

	increment_pipes(&read_pipe, &write_pipe);
	if ((sort_pid = fork()) == 0) {
		sort(&pipes[read_pipe], &pipes[write_pipe]);
    }

	increment_pipes(&read_pipe, &write_pipe);
	if ((pager_pid = fork()) == 0) {	
        pager(&pipes[read_pipe]);
    }

	close_pipes();
	waitpid(printenv_pid, &status, 0);

	if (parameters.size > 1) {
		waitpid(sort_pid, &status, 0);
	}

	waitpid(sort_pid, &status, 0);
    waitpid(pager_pid, &status, 0);

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

void grep (int inpipe[2], int outpipe[2], char** arguments){
    dup2(inpipe[READ], STDIN_FILENO);
    dup2(outpipe[WRITE], STDOUT_FILENO);
    close_pipes();
    if (execvp("grep", arguments) == -1) {
        fprintf(stderr, "Failed to start sort: %s\n", strerror(errno));
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
        fprintf(stderr, "Pipe init failed");
    }
    if (-1 == pipe(pipes + 2)){
        pipes[2] = -1;
        pipes[3] = -1;
        fprintf(stderr, "Pipe init failed");
    }
    if (number_of_pipes == 3){
        if (-1 == pipe(pipes + 4)){
            pipes[4] = -1;
            pipes[5] = -1;
            fprintf(stderr, "Pipe init failed");
        }
    }
    else{
        pipes[4] = -1;
        pipes[5] = -1;
    }
    pipes[6] = -1;
}

void increment_pipes(int *read_pipe, int *write_pipe) {
	*read_pipe += 2;
	*write_pipe += 2;
}
