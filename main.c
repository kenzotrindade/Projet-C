#include <stdio.h>
#include "library.h"

int main() {
    if (file_exist("file.txt") == 0) {
        printf("The file exist.\n");
    } else if (file_exist("file.txt") == 1){
        printf("The file does'nt exist\n");
    }

    printf("Le nombre de noeuds est de : %d\n",sum_node("file.txt"));

    int count_links = links_nodes("file.txt");
    printf("Le nombre de links : %d\n", count_links);
}