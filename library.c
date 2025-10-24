#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

int file_exist(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 1;
    }
    fclose(file);
    return 0;
}

int sum_node(char *filename) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int count = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (strcmp(buffer, "#links") == 0) {
            break;
        }
        if (strcmp(buffer, "#nodes") == 0 || strcmp(buffer, "#start") == 0 
            || strcmp(buffer, "#end") == 0 || strlen(buffer) == 0) {
            continue;
        }
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
            if (buffer[i] == '-') {
                count++;
            }
        }
    }
    fclose(file);
    return count;
}

int start_locate(char *filename) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int found = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (found) {
            fclose(file);
            return atoi(buffer);
        }
        if (strcmp(buffer, "#start") == 0) {
            found = 1;
        }
    }
    fclose(file);
    return 2;
}

int end_locate(char *filename) {
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int found = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (found) {
            fclose(file);
            return atoi(buffer);
        }
        if (strcmp(buffer, "#end") == 0) {
            found = 1;
        }
    }
    fclose(file);
    return 3;
}

Node* find_node(Node **nodes, int size, int id) {
    for (int i=0; i<size;i++) {
        if(nodes[i]->id == id) {
            return nodes[i];
        }
    }
    return NULL;
}
// ToDo changer links_count par next
void add_links(Node *n, Node *links) {
    n->links_count++;
    n->links = realloc(n->links, n->links_count * sizeof(Node*));
    n->links[n->links_count - 1] = links; // Permet de récupérer le head car sinon se fait écraser
}

int file_path(char *filename) {
    FILE *file = fopen(filename, "r");
    int node_count = sum_node(filename);
    Node **nodes = malloc(node_count * sizeof(Node*));
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {

    }
}