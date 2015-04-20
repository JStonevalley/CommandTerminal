#include <dirent.h>
#include "system_navigation.h"

#ifndef COMMANDTERMINAL_ROUTING_H
#define COMMANDTERMINAL_ROUTING_H

#endif

struct string_array tokenizeString(char *command_string);

bool route_command(struct string_array parameters, char **current_location);
