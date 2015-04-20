#include <stdio.h>
#include "system_navigation.h"

void navigate_file_system(struct string_array parameters, DIR *current_dir){
    printf("%i", parameters.size);
    printf("%s", parameters.array[0]);
}