#include <stdio.h>

typedef struct n{
    int id;
    struct n **links;
    int links_count;
}Node;

typedef enum{
    FILE_NOT_FOUND = 1,
    NO_START_NODE = 2,
    NO_END_NODE = 3,
    BAD_FILE_FORMAT = 4
} Error;

int file_exist(char *filename);
int sum_node(char *filename);
int links_nodes(char *filename);
int start_locate(char *filename);
int end_locate(char *filename);
Node* find_node(Node **nodes, int size, int id);
void add_links(Node *n, Node *links);
Node** init_node(char *filename);
void parse_link(char *line, int *id1, int *id2);
void init_links(char *filename, Node **nodes, int node_count);
Node** file_path(char *filename);
void display_nodes(Node *start);
Node** get_unconnected_nodes(Node **nodes, int size, Node *head);
int display_path(Node *start, Node *end);
void print_unconnected(Node **unconnected, int node_count);
void free_memory(Node **nodes, Node **unconnected, int count);