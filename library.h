#include <stdio.h>

typedef struct n{
    int id;
    struct n **links;
    int links_count;
    int visited;
    int distance;
    struct Node **parent;
}Node;

// typedef enum{
//     FILE_NOT_FOUND = 1,
//     NO_START_NODE = 2,
//     NO_END_NODE = 3,
//     BAD_FILE_FORMAT = 4
// } Error;

int file_exist(char *filename);
int sum_node(char *filename);
int links_nodes(char *filename);
int start_locate(char *filename);
int end_locate(char *filename);
Node* find_node(Node **nodes, int size, int id);
void add_links(Node *n, Node *links);
int file_path(char *filename);