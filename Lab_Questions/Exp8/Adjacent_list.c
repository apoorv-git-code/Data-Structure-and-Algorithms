/*Develop a C program to implement an undirected graph using a Vertex List and an Adjacency List.
Store the vertices in an array and use linked lists to represent the adjacency list. The program should
read the number of vertices and edges, accept the vertex labels and edges from the user, construct and
display the adjacency list, find the degree of each vertex, and display the total number of vertices and
edges.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a node in the Adjacency List
struct Node {
    int vertex_idx;
    struct Node* next;
};

// Structure for the Vertex in the Vertex List
struct Vertex {
    char label[20];
    struct Node* head;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex_idx = v;
    newNode->next = NULL;
    return newNode;
}

int main() {
    int num_v, num_e;

    printf("Enter the number of vertices: ");
    scanf("%d", &num_v);
    printf("Enter the number of edges: ");
    scanf("%d", &num_e);

    // Create Vertex List
    struct Vertex vertexList[num_v];

    // Initialize labels and heads
    for (int i = 0; i < num_v; i++) {
        printf("Enter label for vertex %d: ", i);
        scanf("%s", vertexList[i].label);
        vertexList[i].head = NULL;
    }

    // Input edges and build Adjacency List
    printf("\n--- Enter Edges (Source_Index Destination_Index) ---\n");
    for (int i = 0; i < num_e; i++) {
        int src, dest;
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);

        // Since it's undirected, add edge from src to dest
        struct Node* newNode = createNode(dest);
        newNode->next = vertexList[src].head;
        vertexList[src].head = newNode;

        // And add edge from dest to src
        newNode = createNode(src);
        newNode->next = vertexList[dest].head;
        vertexList[dest].head = newNode;
    }

    // Display Adjacency List
    printf("\n--- Adjacency List Representation ---\n");
    for (int i = 0; i < num_v; i++) {
        printf("%s [%d]: ", vertexList[i].label, i);
        struct Node* temp = vertexList[i].head;
        while (temp) {
            printf("-> %s ", vertexList[temp->vertex_idx].label);
            temp = temp->next;
        }
        printf("NULL\n");
    }

    // Display Degrees, Total Vertices, and Total Edges
    printf("\n--- Graph Statistics ---\n");
    printf("Total Vertices: %d\n", num_v);
    printf("Total Edges: %d\n", num_e);
    
    for (int i = 0; i < num_v; i++) {
        int degree = 0;
        struct Node* temp = vertexList[i].head;
        while (temp) {
            degree++;
            temp = temp->next;
        }
        printf("Degree of %s: %d\n", vertexList[i].label, degree);
    }

    // Free memory (Recommended practice)
    for (int i = 0; i < num_v; i++) {
        struct Node* temp = vertexList[i].head;
        while (temp) {
            struct Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    return 0;
}