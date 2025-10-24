#include <stdio.h>
#include "library.h"
#include <string.h>

int file_exist(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 1;
    } else {
        fclose(file);
        return 0;
    }
}
