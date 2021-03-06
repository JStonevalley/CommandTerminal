#ifndef COMMANDTERMINAL_CHECKENV_H
#define COMMANDTERMINAL_CHECKENV_H

typedef int rw;
#define READ 0
#define WRITE 1

bool checkEnv(char *args[], int size);
void printenv(int outpipe[2]);
void grep (int inpipe[2], int outpipe[2], char* args[]);
void sort(int inpipe[2], int outpipe[2]);
void pager(int inpipe[2]);
void close_pipes();
void initiate_pipes(int number_of_pipes);
void increment_pipes(int *read_pipe, int *write_pipe);

#endif
