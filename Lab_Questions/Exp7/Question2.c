#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for the Linked List Node
typedef struct Node {
    char word[50];
    char meaning[200];
    struct Node* next;
} Node;

// Structure for the Hash Table
typedef struct {
    int size;
    Node** table; // Array of pointers to Nodes
} HashTable;

// Custom Hash Function: Sum of ASCII values
int hashFunction(char* str, int table_size) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        sum += (int)str[i];
    }
    return sum % table_size;
}

// Create a new node
Node* createNode(char* word, char* meaning) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->next = NULL;
    return newNode;
}

// Initialize the Hash Table
HashTable* createTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (Node**)malloc(sizeof(Node*) * size);
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Insert word and meaning
void insert(HashTable* ht, char* word, char* meaning) {
    int index = hashFunction(word, ht->size);
    Node* newNode = createNode(word, meaning);
    
    // Add to the head of the linked list (Separate Chaining)
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    printf("Inserted: %s at Index: %d\n", word, index);
}

// Search for a word
void search(HashTable* ht, char* word) {
    int index = hashFunction(word, ht->size);
    Node* temp = ht->table[index];
    
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            printf("Found: [%s] -> %s\n", word, temp->meaning);
            return;
        }
        temp = temp->next;
    }
    printf("Word '%s' not found in dictionary.\n", word);
}

// Delete a word
void deleteWord(HashTable* ht, char* word) {
    int index = hashFunction(word, ht->size);
    Node *temp = ht->table[index], *prev = NULL;

    while (temp != NULL && strcmp(temp->word, word) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Cannot delete: '%s' not found.\n", word);
        return;
    }

    if (prev == NULL) { // Node to delete is the head
        ht->table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Deleted: %s from Index: %d\n", word, index);
}

// Print the entire table
void display(HashTable* ht) {
    printf("\n--- Dictionary State ---\n");
    for (int i = 0; i < ht->size; i++) {
        printf("Index %d: ", i);
        Node* temp = ht->table[i];
        while (temp) {
            printf("[%s: %s] -> ", temp->word, temp->meaning);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("------------------------\n");
}

int main() {
    int size;
    printf("Enter a co-prime (table size): ");
    scanf("%d", &size);

    HashTable* myDict = createTable(size);

    // Test Case 1: Insertions (including collisions)
    insert(myDict, "Apple", "A red fruit");
    insert(myDict, "Map", "A diagram of an area"); // Might collide based on ASCII sum
    insert(myDict, "Amp", "Electronic signal booster");
    
    display(myDict);

    // Test Case 2: Searching
    search(myDict, "Apple");
    search(myDict, "Banana"); // Non-existent

    // Test Case 3: Deletion
    deleteWord(myDict, "Map");
    display(myDict);

    return 0;
}