#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "system_navigation.h"

void cd(char *dir) {
	if (dir == NULL) {
		dir = "/"; /* set to root */
	}

    if (chdir(dir) == -1) {
        printf("Directory change failed: %s\n", strerror(errno));
    }
}
