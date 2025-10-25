#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

int file_exist(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return FILE_NOT_FOUND;
    fclose(file);
    return 0;
}

void clean_line(char *buffer) {
    buffer[strcspn(buffer, "\r\n")] = 0;
}

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

int sum_node(char *filename) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int count = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (strcmp(buffer, "#links") == 0) break;
        if (is_section(buffer)) continue;
        count++;
    }
    fclose(file);
    return count;
}

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

int find_value(char *filename, char *section) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int found = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (found) { // ToDo changer le juste if(found) -> quelque chose de moins cramé et + sécurisé
            fclose(file);
            return atoi(buffer); // ToDo remplacer le atoi si possible
        }
        if (strcmp(buffer, section) == 0) found = 1;
    }
    fclose(file);
    return 0;
}

int start_locate(char *filename) {
    int result = find_value(filename, "#start");
    if (result == 0) {
        return NO_START_NODE;
    }
    return result;
}

int end_locate(char *filename) {
    int result = find_value(filename, "#end");
    if (result == 0) {
        return NO_END_NODE;
    }
    return result;
}

Node* find_node(Node **nodes, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (nodes[i]->id == id) {
            return nodes[i];
        }
    }
    return NULL;
}

void add_links(Node *n, Node *link) {
    n->links_count++;
    n->links = realloc(n->links, n->links_count * sizeof(Node*));
    n->links[n->links_count - 1] = link; // ToDo voir pour quelque chose de + long mais - cramé
}

Node* create_node(int id) {
    Node *node = malloc(sizeof(Node));
    node->id = id;
    node->links_count = 0;
    node->links = NULL;
    return node;
}

Node** init_node(char *filename) {
    FILE *file = fopen(filename, "r");
    int count = sum_node(filename);
    Node **nodes = malloc(count * sizeof(Node*));
    char buffer[256];
    int i = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (is_section(buffer)) {
            continue; }
        if (strcmp(buffer, "#links") == 0) {
            break; }
        nodes[i] = create_node(atoi(buffer)); // ToDo pareil pour le atoi
        i++;
    }
    fclose(file);
    return nodes;
}

void parse_link(char *line, int *id1, int *id2) {
    clean_line(line);
    if (sscanf(line, "%d-%d", id1, id2) != 2) { // ToDo essayer de remplacer le "sscanf"
        *id1 = 0;
        *id2 = 0;
    }
}

void connect_nodes(Node *n1, Node *n2) {
    add_links(n1, n2);
    add_links(n2, n1);
}

void init_links(char *filename, Node **nodes, int count) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int in_links = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        clean_line(buffer);
        if (!in_links) { // ToDo remplacer le !in_links pour - cramé
            if (strcmp(buffer, "#links") == 0) in_links = 1;
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

Node** file_path(char *filename) {
    int size = sum_node(filename);
    Node **nodes = init_node(filename);
    init_links(filename, nodes, size);
    return nodes;
}

void init_bfs(int *visited, int *parent) {
    for (int i = 0; i < 1000; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
}

void init_neighbor(Node *current, Node **queue, int *rear, // ToDo faire la fonction - cramé aussi
                       int *visited, int *parent) {
    for (int i = 0; i < current->links_count; i++) {
        Node *n = current->links[i];
        if (!visited[n->id]) {
            visited[n->id] = 1;
            parent[n->id] = current->id;
            queue[(*rear)++] = n;
        }
    }
}

void display_nodes(Node *start) { // ToDo pareil pour cette fonction là
    if (start == NULL) return;
    int visited[1000] = {0};
    Node *queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = start;
    visited[start->id] = 1;
    
    while (front < rear) {
        Node *current = queue[front++];
        printf("%d ", current->id);
        for (int i = 0; i < current->links_count; i++) {
            Node *n = current->links[i];
            if (!visited[n->id]) {
                visited[n->id] = 1;
                queue[rear++] = n;
            }
        }
    }
    printf("\n");
}

void mark_connected(Node *head, int *visited) { // ToDo pareil ici
    Node *queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = head;
    visited[head->id] = 1;
    
    while (front < rear) {
        Node *current = queue[front++];
        for (int i = 0; i < current->links_count; i++) {
            Node *n = current->links[i];
            if (!visited[n->id]) {
                visited[n->id] = 1;
                queue[rear++] = n;
            }
        }
    }
}

Node** get_unconnected_nodes(Node **nodes, int size, Node *head) { // ToDo pareil ici 
    Node **unconnected = malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) unconnected[i] = NULL;
    
    int visited[1000] = {0};
    mark_connected(head, visited);
    
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (!visited[nodes[i]->id]) {
            unconnected[idx++] = nodes[i];
        }
    }
    return unconnected;
}

void print_path(int *path, int len) {
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");
}

void build_path(int end_id, int *parent, int *path, int *size) {
    int node_id = end_id;
    *size = 0;
    while (node_id != -1) {
        path[(*size)++] = node_id;
        node_id = parent[node_id];
    }
}

int display_path(Node *start, Node *end) { // ToDo pareil rendre - cramé la fonction
    int visited[1000], parent[1000];
    Node *queue[1000];
    int front = 0, rear = 0;
    
    init_bfs(visited, parent);
    queue[rear++] = start;
    visited[start->id] = 1;
    
    while (front < rear) {
        Node *current = queue[front++];
        if (current->id == end->id) {
            int path[1000], len;
            build_path(end->id, parent, path, &len);
            print_path(path, len);
            return 0;
        }
        init_neighbor(current, queue, &rear, visited, parent);
    }
    return 1;
}

void print_unconnected(Node **unconnected, int node_count) {
    int has_unconnected = 0;
    for (int i = 0; i < node_count; i++) {
        if (unconnected[i] != NULL) {
            has_unconnected = 1;
            break;
        }
    }
    if (has_unconnected) {
        printf("unconnected nodes:\n");
        for (int i = 0; i < node_count; i++) {
            if (unconnected[i] != NULL) {
                printf("%d ", unconnected[i]->id);
            }
        }
        printf("\n");
    }
}

void free_memory(Node **nodes, Node **unconnected, int count) {
    free(unconnected);
    for (int i = 0; i < count; i++) {
        free(nodes[i]->links);
        free(nodes[i]);
    }
    free(nodes);
}