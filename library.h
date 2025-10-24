#include <stdio.h>

typedef struct n{
    int id;
    struct n **links;
}Node;

int file_exist(char *filename);

Node** init_node(char *filename);