#include <stdio.h>

typedef struct n{
    int id;
    struct n **links;
}Node;

void file_exist();


Node** init_node(char *filename);

// Node** init_node(char *filename);