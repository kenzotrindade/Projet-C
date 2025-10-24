#include <stdio.h>

typedef struct n{
    int id;
    struct n **links;
}Node;

typedef enum{
    FILE_NOT_FOUND = 1,
    NO_START_NODE = 2,
    NO_END_NODE = 3,
    BAD_FILE_FORMAT = 4
} Error;

int file_exist(char *filename);
int sum_node(char *file);
int links_nodes(char *filename);