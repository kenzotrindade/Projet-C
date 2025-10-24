#include <stdio.h>

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

int main() {
    int count_links = links_nodes("file.txt");
    printf("Le nombre de links : %d\n", count_links);
}