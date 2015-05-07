#include <dirent.h>
#include "structs.h"

#ifndef COMMANDTERMINAL_SYSTEM_NAVIGATION_H
#define COMMANDTERMINAL_SYSTEM_NAVIGATION_H

void cd(struct string_array parameters);

void ls(struct string_array parameters, char **current_dir);
#endif
