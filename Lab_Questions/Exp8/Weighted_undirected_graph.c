// /*Develop a C program to implement a weighted undirected graph using Vertex List and Edge List
// representations. Store the vertices in an array and the edges in an array of structures, where each
// structure contains the source vertex index, destination vertex index, and weight of the edge. The program
// must read the number of vertices and edges, accept vertex labels and weighted edges from the user,
// display the graph details, determine the degree of each vertex, and print the total number of vertices and
// edges.*/




#include <stdio.h>

// Simple structure for the Edge List
struct Edge {
    int u, v, w; // source index, destination index, weight
};

int main() {
    int nV, nE, i, j;
    char labels[20][20]; // Array to store vertex names (max 20 vertices)
    struct Edge edges[100]; // Array of structures (max 100 edges)

    // 1. Inputs
    printf("Enter number of vertices: ");
    scanf("%d", &nV);
    printf("Enter number of edges: ");
    scanf("%d", &nE);

    // 2. Vertex List Input
    for (i = 0; i < nV; i++) {
        printf("Enter label for vertex %d: ", i);
        scanf("%s", labels[i]);
    }

    // 3. Edge List Input
    for (i = 0; i < nE; i++) {
        printf("Enter edge %d (src_idx dest_idx weight): ", i + 1);
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // 4. Display Graph Details
    printf("\n--- Graph Details ---\n");
    printf("Total Vertices: %d\n", nV);
    printf("Total Edges: %d\n", nE);
    for (i = 0; i < nE; i++) {
        printf("Edge: %s - %s | Weight: %d\n", labels[edges[i].u], labels[edges[i].v], edges[i].w);
    }

    // 5. Degree Calculation
    printf("\n--- Degrees ---\n");
    for (i = 0; i < nV; i++) {
        int degree = 0;
        for (j = 0; j < nE; j++) {
            // Count if vertex i is either the start or end of the edge
            if (edges[j].u == i) degree++;
            if (edges[j].v == i) degree++;
        }
        printf("Vertex %s: Degree %d\n", labels[i], degree);
    }

    return 0;
}