#include <stdio.h>
#include "library.h"

int main() {
    if (file_exist("file.txt") == 0) {
        printf("The file exist.\n");
    } else if (file_exist("file.txt") == 1){
        printf("The file does'nt exist\n");
    }

    printf("nodes: %d\n",sum_node("file.txt"));

    int count_links = links_nodes("file.txt");
    printf("links: %d\n", count_links);
    printf("start: %d\n", start_locate("file.txt"));
    printf("end: %d\n", end_locate("file.txt"));
}
