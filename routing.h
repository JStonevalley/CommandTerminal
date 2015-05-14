#include <dirent.h>
#include "system_navigation.h"

#ifndef COMMANDTERMINAL_ROUTING_H
#define COMMANDTERMINAL_ROUTING_H

void tokenize_string(char* input, char *args[], int *size, bool *background);
bool route_command(char *args[], int size, bool background);
bool contains_ampersand(char *args[], int size);

#endif


