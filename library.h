#define MAX_NODE_ID 1000


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
int check_file_format(char *filename);
void clean_line(char *buffer);
int is_section(char *line);
int sum_node(char *filename);
int links_nodes(char *filename);
int string_to_number(char *str);
int find_value(char *filename, char *section);
int start_locate(char *filename);
int end_locate(char *filename);
Node* find_node(Node **nodes, int size, int id);
void add_links(Node *n, Node *links);
Node* create_node(int id);
Node** init_node(char *filename);
int parse_first_number(char *line);
int parse_second_number(char *line); 
void parse_link(char *line, int *id1, int *id2);
void connect_nodes(Node *n1, Node *n2);
void init_links(char *filename, Node **nodes, int node_count);
Node** file_path(char *filename);
void init_arrays(int *visited, int *parent);
void add_next(Node *current, Node **queue, int *rear,
                             int *visited, int *parent);
void display_nodes(Node *start);
void connected(Node *head, int *visited);
Node** get_unconnected_nodes(Node **nodes, int size, Node *head);
void print_path(int *path, int len);
void build_path(int end_id, int *parent, int *path, int *size);
int display_path(Node *start, Node *end);
void print_unconnected(Node **unconnected, int node_count);
void free_memory(Node **nodes, Node **unconnected, int count);