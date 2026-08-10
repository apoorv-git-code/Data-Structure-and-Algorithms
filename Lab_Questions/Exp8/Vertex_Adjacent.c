/*Develop a menu-driven C program to represent a weighted graph using a Vertex List and an Adjacency
Matrix, where the vertex list is stored as a one-dimensional array and the adjacency matrix is stored as
a two-dimensional array. The program should read the number of vertices from the user, create the
required arrays within main(), accept the vertex labels and the weighted adjacency matrix as input, and
provide suitable menu options to perform the required graph operations. The program shall include the
following functionalities:
a. Display the vertex list and total number of vertices,
b. Display the adjacency matrix and total number of edges,
c. Determine whether the given graph is directed or undirected by examining the symmetry of
the adjacency matrix. Also compute and display the degree of each vertex if the graph is
undirected, or the in-degree and out-degree of each vertex if the graph is directed.
Assumption: A value of 0 in the adjacency matrix indicates the absence of an edge, any non-zero value
indicates the weight of the edge.*/



#include <stdio.h>
#include <stdbool.h>

#define MAX 20

// Function Prototypes
void displayVertices(char vertices[][10], int n);
void displayMatrix(int adj[MAX][MAX], int n);
bool isUndirected(int adj[MAX][MAX], int n);
void calculateDegrees(char vertices[][10], int adj[MAX][MAX], int n);

int main() {
    int n, i, j, choice;
    char vertices[MAX][10];
    int adj[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Input Vertex Labels
    printf("Enter the labels for %d vertices:\n", n);
    for (i = 0; i < n; i++) {
        printf("Vertex %d: ", i);
        scanf("%s", vertices[i]);
    }

    // Input Adjacency Matrix
    printf("\nEnter the weighted adjacency matrix (use 0 for no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Weight for [%s][%s]: ", vertices[i], vertices[j]);
            scanf("%d", &adj[i][j]);
        }
    }

    do {
        printf("\n--- Graph Operations Menu ---");
        printf("\n1. Display Vertex List");
        printf("\n2. Display Adjacency Matrix & Edge Count");
        printf("\n3. Analyze Graph Type and Degrees");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayVertices(vertices, n);
                break;
            case 2:
                displayMatrix(adj, n);
                break;
            case 3:
                calculateDegrees(vertices, adj, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}

void displayVertices(char vertices[][10], int n) {
    printf("\n--- Vertex List ---\n");
    for (int i = 0; i < n; i++) {
        printf("Index %d: %s\n", i, vertices[i]);
    }
    printf("Total number of vertices: %d\n", n);
}

void displayMatrix(int adj[MAX][MAX], int n) {
    int edgeCount = 0;
    bool undirected = isUndirected(adj, n);

    printf("\n--- Adjacency Matrix ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", adj[i][j]);
            if (adj[i][j] != 0) edgeCount++;
        }
        printf("\n");
    }

    // For undirected graphs, each edge is counted twice in the matrix (i,j and j,i)
    if (undirected) {
        // Count self-loops once, other edges twice
        int selfLoops = 0;
        for(int i=0; i<n; i++) if(adj[i][i] != 0) selfLoops++;
        printf("Total number of edges: %d\n", (edgeCount - selfLoops) / 2 + selfLoops);
    } else {
        printf("Total number of edges: %d\n", edgeCount);
    }
}

bool isUndirected(int adj[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != adj[j][i]) return false;
        }
    }
    return true;
}

void calculateDegrees(char vertices[][10], int adj[MAX][MAX], int n) {
    if (isUndirected(adj, n)) {
        printf("\nGraph Type: Undirected (Symmetric Matrix)\n");
        for (int i = 0; i < n; i++) {
            int degree = 0;
            for (int j = 0; j < n; j++) {
                if (adj[i][j] != 0) {
                    degree++;
                    if (i == j) degree++; // Self-loops count twice in undirected degrees
                }
            }
            printf("Vertex %s: Degree = %d\n", vertices[i], degree);
        }
    } else {
        printf("\nGraph Type: Directed (Asymmetric Matrix)\n");
        for (int i = 0; i < n; i++) {
            int inDegree = 0, outDegree = 0;
            for (int j = 0; j < n; j++) {
                if (adj[i][j] != 0) outDegree++; // Row sum
                if (adj[j][i] != 0) inDegree++;  // Column sum
            }
            printf("Vertex %s: In-Degree = %d, Out-Degree = %d\n", vertices[i], inDegree, outDegree);
        }
    }
}