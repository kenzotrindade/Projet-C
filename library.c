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

int links_nodes(char *filename) {
    FILE *file = fopen(filename, "r");
    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        for (int i=0;buffer[i] != '\0'; i++) {
            if (buffer[i] == '-') {
                count++;
            }  
        }
    }
    return count;
    fclose(file);
}