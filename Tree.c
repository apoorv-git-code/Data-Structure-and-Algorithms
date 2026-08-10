#include<stdio.h> // Include standard input/output library for printf and scanf

#define MAX 100 // Define the maximum size of the tree array

int tree[MAX]; // Array to store the binary tree nodes

// initialize tree
void init()
{
    for(int i = 0; i < MAX; i++)
        tree[i] = -1; // -1 indicates that the node is empty (no value present)
}

// insert at given index
void insert(int index, int value)
{
    if(index >= MAX) // Check if the index exceeds the array bounds
    {
        printf("Index out of range\n");
        return; // Exit the function if out of bounds
    }

    tree[index] = value; // Store the given value at the specified index
}

// display tree (array form)
void display()
{
    printf("Tree elements:\n");

    for(int i = 0; i < MAX; i++)
    {
        if(tree[i] != -1) // Only print the nodes that have been initialized (not -1)
            printf("Index %d → %d\n", i, tree[i]);
    }
}

// get left child
void getLeft(int index)
{
    int i = 2*index + 1; // Formula to find the left child index in an array representation

    if(i < MAX && tree[i] != -1) // Check if left child exists within bounds and is not empty
        printf("Left child of %d = %d\n", tree[index], tree[i]);
    else
        printf("No left child\n");
}

// get right child
void getRight(int index)
{
    int i = 2*index + 2; // Formula to find the right child index in an array representation

    if(i < MAX && tree[i] != -1) // Check if right child exists within bounds and is not empty
        printf("Right child of %d = %d\n", tree[index], tree[i]);
    else
        printf("No right child\n");
}

// get parent
void getParent(int index)
{
    if(index == 0) // The root node (index 0) has no parent
    {
        printf("Root node has no parent\n");
        return;
    }

    int i = (index - 1) / 2; // Formula to find the parent index in an array representation

    if(tree[i] != -1) // Check if parent exists
        printf("Parent of %d = %d\n", tree[index], tree[i]);
    else
        printf("No parent\n");
}

int main()
{
    int choice, index, value; // Variables to store user input
    init(); // Initialize the tree array with -1

    printf("\n--- Tree Operations Menu ---\n");
    printf("1. Insert node\n");
    printf("2. Display tree\n");
    printf("3. Get Left Child\n");
    printf("4. Get Right Child\n");
    printf("5. Get Parent\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice); // Read user's menu choice

    switch (choice) {
        case 1:
            printf("Enter index: ");
            scanf("%d", &index); // Read index where the node will be inserted
            printf("Enter value: ");
            scanf("%d", &value); // Read the value of the new node
            insert(index, value); // Call insert function to add the node
            break; // Exit switch block
        case 2:
            display(); // Call display function to show all tree nodes
            break;
        case 3:
            printf("Enter index of node to get left child: ");
            scanf("%d", &index); // Read the index of the parent node
            getLeft(index); // Call getLeft function
            break;
        case 4:
            printf("Enter index of node to get right child: ");
            scanf("%d", &index); // Read the index of the parent node
            getRight(index); // Call getRight function
            break;
        case 5:
            printf("Enter index of node to get parent: ");
            scanf("%d", &index); // Read the index of the child node
            getParent(index); // Call getParent function
            break;
        case 6:
            printf("Exiting...\n");
            return 0; // Terminate the program
        default:
            printf("Invalid choice! Please try again.\n"); // Handle invalid inputs
    }

    return 0; // Standard main return
}