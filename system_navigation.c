#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "system_navigation.h"

/*
	Navigate to the indicated directory.
	If there is an error it is printed.
*/
void cd(char *dir) {
	if (dir == NULL) {
		dir = "/"; /* set to root */
	}
    if (chdir(dir) == -1) {
        printf("Directory change failed: %s\n", strerror(errno));
    }
}
