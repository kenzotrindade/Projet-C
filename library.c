#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
// ToDo faire un système de ./pathfinding "Mon fichier" en terminal
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

Node** init_node(char *filename){
    FILE *file = fopen(filename, "r");
    int count = sum_node(filename);
    Node **nodes = malloc(count + 1 * sizeof(Node*));
    char buffer[256];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (strcmp(buffer, "#nodes") == 0 || strcmp(buffer, "#start") == 0 
            || strcmp(buffer, "#end") == 0 || strlen(buffer) == 0) {
            continue;
        }
        if (strcmp(buffer, "#links") == 0) {
            break;
        }else {
            nodes[i] = malloc(sizeof(Node));
            nodes[i]->id = atoi(buffer);
            nodes[i]->links_count = 0;
            nodes[i]->links = NULL;
            i++;
        }
    }
    fclose(file);
    return nodes;
}

// ToDo faire une fonctions free qui est sur chatgpt

void parse_link(char *line, int *id1, int *id2) {
    line[strcspn(line, "\r\n")] = 0;
    if (sscanf(line, "%d-%d", id1, id2) != 2) {
        *id1 = -1;
        *id2 = -1;
    }
}


void init_links(char *filename, Node **nodes, int node_count){
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int in_links = 0; 
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (!in_links) {
            if (strcmp(buffer, "#links") == 0) in_links = 1; 
            continue; 
        }
        int id1, id2;
        parse_link(buffer, &id1, &id2);
        if (id1 != -1 && id2 != -1) {
            Node *n1 = find_node(nodes, node_count, id1);
            Node *n2 = find_node(nodes, node_count, id2);
            add_links(n1, n2);
            add_links(n2, n1);
        }
    }
    fclose(file);
}



Node** file_path(char *filename) {
    int size = sum_node(filename);
    Node **nodes = init_node(filename);  // initialise tous les nodes
    init_links(filename, nodes, size);   // initialise les liens

    int index_start = start_locate(filename);
    int index_end   = end_locate(filename);

    Node *start = find_node(nodes, size, index_start);
    Node *end   = find_node(nodes, size, index_end);

    return nodes; // on retourne le tableau de nodes initialisé et relié
}