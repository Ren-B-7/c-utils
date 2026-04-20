#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "minunit.h"

/* --- Graph Example --- */

// This example demonstrates the graph data structure.
// It shows how to create a graph, add vertices and edges,
// and perform basic traversals like BFS.

// Define a simple data structure to store in graph nodes
typedef struct node_data {
    int id;
    char name[50];
} node_data_t;

// Callback for comparing node data (e.g., by ID)
bool compare_node_data(void *data1, void *data2) {
    node_data_t *nd1 = (node_data_t *)data1;
    node_data_t *nd2 = (node_data_t *)data2;
    return nd1 != NULL && nd2 != NULL && nd1->id == nd2->id;
}

// Callback for printing node data (for BFS/DFS visualization)
void print_node_data(void *data) {
    node_data_t *nd = (node_data_t *)data;
    if (nd) {
        printf("ID: %d, Name: %s", nd->id, nd->name);
    }
}

// Callback for freeing node data
void free_node_data(void *data) {
    free(data);
}

char *test_graph_vertex_edge_operations() {
    // Create a graph
    graph_t *g = graph_create(compare_node_data, print_node_data, free_node_data);
    mu_assert("graph_create failed", g != NULL);

    // Add vertices
    node_data_t *data1 = (node_data_t *)malloc(sizeof(node_data_t));
    data1->id = 1; strcpy(data1->name, "Node A");
    node_t *v1 = graph_add_vertex(g, data1);
    mu_assert("graph_add_vertex failed for v1", v1 != NULL);

    node_data_t *data2 = (node_data_t *)malloc(sizeof(node_data_t));
    data2->id = 2; strcpy(data2->name, "Node B");
    node_t *v2 = graph_add_vertex(g, data2);
    mu_assert("graph_add_vertex failed for v2", v2 != NULL);

    node_data_t *data3 = (node_data_t *)malloc(sizeof(node_data_t));
    data3->id = 3; strcpy(data3->name, "Node C");
    node_t *v3 = graph_add_vertex(g, data3);
    mu_assert("graph_add_vertex failed for v3", v3 != NULL);

    // Add edges (directed graph assumed, adjust if undirected)
    // Edge from v1 to v2
    mu_assert("graph_add_edge failed v1->v2", graph_add_edge(g, v1, v2) == SUCCESS);
    // Edge from v1 to v3
    mu_assert("graph_add_edge failed v1->v3", graph_add_edge(g, v1, v3) == SUCCESS);
    // Edge from v2 to v3
    mu_assert("graph_add_edge failed v2->v3", graph_add_edge(g, v2, v3) == SUCCESS);

    // Check graph properties
    mu_assert("graph_num_vertices incorrect", graph_num_vertices(g) == 3);
    mu_assert("graph_num_edges incorrect", graph_num_edges(g) == 3);

    // Find a vertex
    node_data_t search_data = {2, ""}; // Search by ID
    node_t *found_v = graph_find_vertex(g, &search_data);
    mu_assert("graph_find_vertex failed", found_v != NULL);
    mu_assert("graph_find_vertex returned wrong vertex", ((node_data_t *)graph_vertex_data(found_v))->id == 2);

    // Test removing a vertex (should also remove incident edges)
    graph_remove_vertex(g, v1);
    mu_assert("graph_num_vertices incorrect after removing v1", graph_num_vertices(g) == 2);
    mu_assert("graph_num_edges incorrect after removing v1", graph_num_edges(g) == 1); // v2->v3 remains
    mu_assert("graph_find_vertex still found removed v1", graph_find_vertex(g, data1) == NULL);


    // Re-add v1 to test BFS
    node_data_t *data1_readd = (node_data_t *)malloc(sizeof(node_data_t));
    data1_readd->id = 1; strcpy(data1_readd->name, "Node A Readded");
    v1 = graph_add_vertex(g, data1_readd);
    graph_add_edge(g, v1, v2); // v1 -> v2
    graph_add_edge(g, v1, v3); // v1 -> v3
    graph_add_edge(g, v2, v3); // v2 -> v3

    // Test BFS traversal starting from v1
    printf("
--- BFS Traversal from Node A (ID 1) ---
");
    // BFS typically prints or collects visited nodes.
    // For this test, we'll check if the count is correct.
    // A more robust test would capture printed output or check a returned list.
    int visited_count = 0;
    void **visited_nodes = graph_bfs(g, v1, &visited_count); // Assuming BFS returns an array of visited node data pointers
    mu_assert("graph_bfs failed", visited_nodes != NULL);
    mu_assert("BFS visited count incorrect", visited_count == 3); // Should visit v1, v2, v3

    // Free visited nodes array (if graph_bfs allocates it)
    // This depends on graph.c implementation. Assuming it needs freeing.
    free(visited_nodes);


    graph_destroy(g); // Clean up
    return NULL;
}

// Minunit runner for graph tests
char *(*all_tests[])() = {
    test_graph_vertex_edge_operations,
    NULL
};

int main() {
    return run_all_tests(all_tests);
}
