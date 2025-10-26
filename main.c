#include <stdio.h>
#include <stdlib.h>
#include "library.h"

// 28 lignes 
int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    char *filename = argv[1];
    if (file_exist(filename)) return FILE_NOT_FOUND;
    if (check_file_format(filename)) return BAD_FILE_FORMAT;
    int start_id = start_locate(filename);
    if (start_id == 0) return NO_START_NODE;
    int end_id = end_locate(filename);
    if (end_id == 0) return NO_END_NODE;
    int node_count = sum_node(filename);
    int link_count = links_nodes(filename);
    Node **nodes = init_node(filename);
    init_links(filename, nodes, node_count);
    Node *start_node = find_node(nodes, node_count, start_id);
    Node *end_node = find_node(nodes, node_count, end_id);
    printf("nodes: %d\n", node_count);
    printf("links: %d\n", link_count);
    printf("start: %d\n", start_id);
    printf("end: %d\n", end_id);
    Node **unconnected = get_unconnected_nodes(nodes, node_count, 
                                                start_node);
    print_unconnected(unconnected, node_count);
    printf("pathfinding:\n");
    display_path(start_node, end_node);
    free_memory(nodes, unconnected, node_count);
    return 0;
}