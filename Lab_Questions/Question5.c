#include <stdio.h>
#include <limits.h>

/* (a) Display level-order and check for gaps */
void displayAndCheckGaps(int tree[], int n) {
    int lastValidIndex = -1;
    int hasGaps = 0; // Using 0 for false

    for (int i = 0; i < n; i++) {
        if (tree[i] != -1)
         lastValidIndex = i;
    }

    if (lastValidIndex == -1) {
        printf("The tree is empty.\n");
        return;
    }

    printf("Level-order traversal: ");
    for (int i = 0; i <= lastValidIndex; i++) {
        if (tree[i] != -1) {
            printf("%d ", tree[i]);
        } 
        else {
            hasGaps = 1; // Using 1 for true
        }
    }
    printf("\nArray representation has gaps: %s\n", hasGaps ? "Yes" : "No");
}

/* (b) Node properties and counts */
void analyzeNodes(int tree[], int n, int queryIndex) {
    int totalInternal = 0;
    int totalLeaves = 0;

    for (int i = 0; i < n; i++) {
        if (tree[i] != -1) {
            int leftIdx = 2 * i + 1;
            int rightIdx = 2 * i + 2;
            int hasLeft = (leftIdx < n && tree[leftIdx] != -1);
            int hasRight = (rightIdx < n && tree[rightIdx] != -1);

            if (hasLeft || hasRight)
             totalInternal++;
            else totalLeaves++;
        }
    }

    printf("\nTotal Internal Nodes: %d\n", totalInternal);
    printf("Total Leaf Nodes: %d\n", totalLeaves);

    if (queryIndex < 0 || queryIndex >= n || tree[queryIndex] == -1) {
        printf("Invalid index or node is missing.\n");
        return;
    }

    int p = (queryIndex - 1) / 2;
    int l = 2 * queryIndex + 1;
    int r = 2 * queryIndex + 2;

    printf("\n--- Node Info (Index %d, Value %d) ---\n", queryIndex, tree[queryIndex]);
    printf("Parent: %s\n", (queryIndex == 0) ? "None" : ""); 
    if (queryIndex > 0)
     printf("%d\n", tree[p]);
    
    printf("Left Child: %d, Right Child: %d\n", 
           (l < n) ? tree[l] : -1, (r < n) ? tree[r] : -1);
    
    int degree = ((l < n && tree[l] != -1) ? 1 : 0) + ((r < n && tree[r] != -1) ? 1 : 0);
    printf("Degree: %d, Type: %s\n", degree, (degree == 0) ? "Leaf" : "Internal");
}

/* (c) Check BST property using Inorder traversal logic */
int isBSTInorder(int tree[], int n, int index, int *prev) {
    if (index >= n || tree[index] == -1) return 1;

    if (!isBSTInorder(tree, n, 2 * index + 1, prev)) return 0;

    if (tree[index] <= *prev) return 0;
    *prev = tree[index];

    return isBSTInorder(tree, n, 2 * index + 2, prev);
}

int main() {
    
    int tree[] = {10, 5, 15, 2, -1, -1, 20}; 
    int n = sizeof(tree) / sizeof(tree[0]);
    int prev = INT_MIN;

    printf("=== Array-Based Binary Tree Analysis ===\n");
    displayAndCheckGaps(tree, n);
    analyzeNodes(tree, n, 1);
    
    if (isBSTInorder(tree, n, 0, &prev))
        printf("\nSatisfies BST Property: Yes\n");
    else
        printf("\nSatisfies BST Property: No\n");

    return 0;
}