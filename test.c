#include <stdio.h>
#include "library.h"
#include <string.h>

typedef enum{
    FILE_NOT_FOUND = 1,
    NO_START_NODE = 2,
    NO_END_NODE = 3,
    BAD_FILE_FORMAT = 4
} Error;

int sum_node(char *file) {
    int compt = 0;
    char buffer[256];
    FILE *filen = fopen(file, "r");
    while (fgets(buffer, sizeof(buffer), filen) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        printf("%s\n", buffer); 
        if (strcmp(buffer, "#links") == 0) {
            break;
        }
        if (strcmp(buffer, "#nodes") == 0 ||
            strcmp(buffer, "#start") == 0 ||
            strcmp(buffer, "#end") == 0) {
            continue;
        }
        compt += 1;
    }
    fclose(filen);
    return compt;
}

int main(){
    printf("\n%d",sum_node("file.txt"));
}