#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

// 8 lignes 
int file_exist(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("FILE_NOT_FOUND\n");
        return FILE_NOT_FOUND;
    }
    fclose(file);
    return 0;
}

// 19 lignes 
int check_file_format(char *filename){
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int node = 0, links = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (strcmp(buffer, "#nodes") == 0) node = 1;
        if (strcmp(buffer, "#links") == 0) links = 1;
    }

    if (node == 0 || links == 0){
        printf("BAD_FILE_FORMAT\n");
        fclose(file);
        return BAD_FILE_FORMAT;
    }

    fclose(file);
    return 0;
}

// 3 lignes 
void clean_line(char *buffer) {
    buffer[strcspn(buffer, "\r\n")] = 0;
}

// 14 lignes 
int is_section(char *line) {
    if (strcmp(line, "#nodes") == 0) {
        return 1;
    }
    if (strcmp(line, "#start") == 0) {
        return 1;
    }
    if (strcmp(line, "#end") == 0) {
        return 1;
    }
    if (strlen(line) == 0) {
        return 1;
    }
    return 0;
}

// 17 lignes 
int sum_node(char *filename) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int count = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (strcmp(buffer, "#links") == 0) {
            break;
        }
        if (is_section(buffer)) {
            continue;
        }
        count++;
    }
    fclose(file);
    return count;
}

// 12 lignes 
int links_nodes(char *filename) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int count = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == '-') count++;
        }
    }
    fclose(file);
    return count;
}

// 8 lignes 
int string_to_number(char *str) {
    int result = 0;
    int i = 0;
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

// 17 lignes 
int find_value(char *filename, char *section) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int section_found = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (section_found == 1) {
            fclose(file);
            return string_to_number(buffer);
        }
        if (strcmp(buffer, section) == 0) {
            section_found = 1;
        }
    }
    fclose(file);
    return 0;
}

// 7 lignes 
int start_locate(char *filename) {
    int result = find_value(filename, "#start");
    if (result == 0) {
        printf("NO_START_NODE\n");
        return 0;
    }
    return result;
}

// 7 lignes 
int end_locate(char *filename) {
    int result = find_value(filename, "#end");
    if (result == 0) {
        printf("NO_END_NODE\n");
        return 0;
    }
    return result;
}

// 7 lignes 
Node* find_node(Node **nodes, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (nodes[i]->id == id) {
            return nodes[i];
        }
    }
    return NULL;
}

// 6 lignes 
void add_links(Node *n, Node *link) {
    int new_count = n->links_count + 1;
    Node **new_links = realloc(n->links, new_count * sizeof(Node*));
    new_links[n->links_count] = link;
    n->links = new_links;
    n->links_count = new_count;
}

// 6 lignes 
Node* create_node(int id) {
    Node *node = malloc(sizeof(Node));
    node->id = id;
    node->links_count = 0;
    node->links = NULL;
    return node;
}

// 20 lignes 
Node** init_node(char *filename) {
    FILE *file = fopen(filename, "r");
    int count = sum_node(filename);
    Node **nodes = malloc(count * sizeof(Node*));
    char buffer[256];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (is_section(buffer)) continue;
        if (strcmp(buffer, "#links") == 0) break;
        int node_id = string_to_number(buffer);
        if (node_id > MAX_NODE_ID) {
            printf("Error: node ID too large (%d > %d)\n", node_id, MAX_NODE_ID);
            exit(1);
        }
        nodes[i] = create_node(node_id);
        i++;
    }
    fclose(file);
    return nodes;
}

// 8 lignes 
int parse_first_number(char *line) {
    int num = 0;
    int i = 0;
    while (line[i] >= '0' && line[i] <= '9') {
        num = num * 10 + (line[i] - '0');
        i++;
    }
    return num;
}

// 14 lignes 
int parse_second_number(char *line) {
    int i = 0;
    while (line[i] != '-' && line[i] != '\0') {
        i++;
    }
    if (line[i] == '-') {
        i++;
    }
    int num = 0;
    while (line[i] >= '0' && line[i] <= '9') {
        num = num * 10 + (line[i] - '0');
        i++;
    }
    return num;
}

// 8 lignes 
void parse_link(char *line, int *id1, int *id2) {
    clean_line(line);
    *id1 = parse_first_number(line);
    *id2 = parse_second_number(line);
    if (*id1 == 0 || *id2 == 0) {
        *id1 = 0;
        *id2 = 0;
    }
}

// 4 lignes 
void connect_nodes(Node *n1, Node *n2) {
    add_links(n1, n2);
    add_links(n2, n1);
}

// 20 lignes 
void init_links(char *filename, Node **nodes, int count) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int links_section = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (links_section == 0) {
            if (strcmp(buffer, "#links") == 0) {
                links_section = 1;
            }
            continue;
        }
        int id1, id2;
        parse_link(buffer, &id1, &id2);
        if (id1 == 0 || id2 == 0) continue;
        Node *n1 = find_node(nodes, count, id1);
        Node *n2 = find_node(nodes, count, id2);
        if (n1 != NULL && n2 != NULL) connect_nodes(n1, n2);
    }
    fclose(file);
}

// 5 lignes 
Node** file_path(char *filename) {
    int size = sum_node(filename);
    Node **nodes = init_node(filename);
    init_links(filename, nodes, size);
    return nodes;
}

// 5 lignes 
void init_arrays(int *visited, int *parent) {
    for (int i = 0; i < 1000; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
}

// 12 lignes 
void add_next(Node *current, Node **queue, int *rear,
                             int *visited, int *parent) {
    for (int i = 0; i < current->links_count; i++) {
        Node *next = current->links[i];
        int next_id = next->id;
        if (visited[next_id] == 0) {
            visited[next_id] = 1;
            parent[next_id] = current->id;
            queue[*rear] = next;
            *rear = *rear + 1;
        }
    }
}

// 20 lignes 
void display_nodes(Node *start) {
    int visited[1000] = {0}, front = 0, rear = 0;
    Node *queue[1000];
    queue[rear] = start;
    rear = rear + 1;
    visited[start->id] = 1;
    while (front < rear) {
        Node *current = queue[front];
        front = front + 1;
        printf("%d ", current->id);
        for (int i = 0; i < current->links_count; i++) {
            Node *neighbor = current->links[i];
            if (visited[neighbor->id] == 0) {
                visited[neighbor->id] = 1;
                queue[rear] = neighbor;
                rear = rear + 1;
            }
        }
    }
    printf("\n");
}

// 19 lignes 
void connected(Node *head, int *visited) {
    Node *queue[1000];
    int front = 0;
    int rear = 0;
    queue[rear] = head;
    rear = rear + 1;
    visited[head->id] = 1;
    while (front < rear) {
        Node *current = queue[front];
        front = front + 1;
        for (int i = 0; i < current->links_count; i++) {
            Node *neighbor = current->links[i];
            if (visited[neighbor->id] == 0) {
                visited[neighbor->id] = 1;
                queue[rear] = neighbor;
                rear = rear + 1;
            }
        }
    }
}

// 17 lignes 
Node** get_unconnected_nodes(Node **nodes, int size, Node *head) {
    Node **unconnected = malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        unconnected[i] = NULL;
    }
    
    int visited[1000] = {0};
    connected(head, visited);
    
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (visited[nodes[i]->id] == 0) {
            unconnected[index] = nodes[i];
            index = index + 1;
        }
    }
    return unconnected;
}

// 6 lignes 
void print_path(int *path, int len) {
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");
}

// 8 lignes 
void build_path(int end_id, int *parent, int *path, int *size) {
    int node_id = end_id;
    *size = 0;
    while (node_id != -1) {
        path[*size] = node_id;
        *size = *size + 1;
        node_id = parent[node_id];
    }
}

// 21 lignes 
int display_path(Node *start, Node *end) {
    int visited[1000], parent[1000], front = 0, rear = 0;
    Node *queue[1000];
    init_arrays(visited, parent);
    queue[rear] = start;
    rear = rear + 1;
    visited[start->id] = 1;
    while (front < rear) {
        Node *current = queue[front];
        front = front + 1;
        if (current->id == end->id) {
            int path[1000];
            int len;
            build_path(end->id, parent, path, &len);
            print_path(path, len);
            return 0;
        }
        add_next(current, queue, &rear, 
                               visited, parent);
    }
    return 1;
}

// 17 lignes 
void print_unconnected(Node **unconnected, int node_count) {
    int has_unconnected = 0;
    for (int i = 0; i < node_count; i++) {
        if (unconnected[i] != NULL) {
            has_unconnected = 1;
            break;
        }
    }
    if (has_unconnected == 1) {
        printf("unconnected nodes:\n");
        for (int i = 0; i < node_count; i++) {
            if (unconnected[i] != NULL) {
                printf("%d ", unconnected[i]->id);
            }
        }
        printf("\n");
    }
}

// 7 lignes 
void free_memory(Node **nodes, Node **unconnected, int count) {
    free(unconnected);
    for (int i = 0; i < count; i++) {
        free(nodes[i]->links);
        free(nodes[i]);
    }
    free(nodes);
}
