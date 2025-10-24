#include <stdio.h>
#include "library.h"

int main() {
    if (file_exist("file.txt")) return printf("File doesn't exist.\n"), 1;
    int node_count = sum_node("file.txt");
    printf("%d",node_count);
    Node **nodes = init_node("file.txt");
    init_links("file.txt", nodes, node_count);
    int start_id = start_locate("file.txt");
    int end_id   = end_locate("file.txt");
    Node *start_node = find_node(nodes, node_count, start_id);
    Node *end_node   = find_node(nodes, node_count, end_id);
    if (!start_node || !end_node) return printf("Start or end node not found.\n"), 1;
    printf("nodes: %d, start: %d, end: %d\n", node_count, start_id, end_id);
    for (int i = 0; i < node_count; i++) {
        printf("Node %d linked to: ", nodes[i]->id);
        for (int j = 0; j < nodes[i]->links_count; j++)
            printf("%d ", nodes[i]->links[j]->id);
        printf("\n");
    }
    return 0;
}

