#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count = 0;

// Correct Structure Definition
struct node {
    int no;
    struct node *next;
    struct node *prev;
};

struct node *new_node, *ptr, *temp, *first = NULL, *last = NULL;

// Helper to create a single new node
void get_element() {
    new_node = (struct node*) malloc(sizeof(struct node));
    if (new_node != NULL) {
        printf("Enter data to insert: ");
        scanf("%d", &new_node->no);
        new_node->next = NULL;
        new_node->prev = NULL;
    } else {
        printf("\nDMA unsuccessful. Try again later.\n");
    }
}

void insert_begin() {
    get_element();
    if (first == NULL) {
        first = last = new_node;
    } else {
        new_node->next = first;
        first->prev = new_node;
        first = new_node;
    }
    count++;
    printf("Element inserted at beginning.\n");
}

void insert_end() {
    if (first == NULL) {
        insert_begin();
        return;
    }
    get_element();
    last->next = new_node;
    new_node->prev = last;
    last = new_node;
    count++;
    printf("Element inserted at end.\n");
}

void create_list() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        insert_end();
    }
}

void insert_pos() {
    int pos;
    printf("Enter position (1 to %d): ", count + 1);
    scanf("%d", &pos);

    if (pos == 1) insert_begin();
    else if (pos == count + 1) insert_end();
    else if (pos > 1 && pos <= count) {
        get_element();
        ptr = first;
        for (int i = 1; i < pos - 1; i++) ptr = ptr->next;

        temp = ptr->next;
        new_node->next = temp;
        new_node->prev = ptr;
        ptr->next = new_node;
        temp->prev = new_node;
        count++;
        printf("Element inserted at position %d.\n", pos);
    } else {
        printf("Invalid position!\n");
    }
}

void delete_begin() {
    if (first == NULL) return;
    temp = first;
    if (first == last) {
        first = last = NULL;
    } else {
        first = first->next;
        first->prev = NULL;
    }
    free(temp);
    count--;
    printf("Deleted from beginning.\n");
}

void delete_end() {
    if (last == NULL) return;
    temp = last;
    if (first == last) {
        first = last = NULL;
    } else {
        last = last->prev;
        last->next = NULL;
    }
    free(temp);
    count--;
    printf("Deleted from end.\n");
}

void display() {
    if (first == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("\nElements in List (%d): ", count);
    ptr = first;
    while (ptr != NULL) {
        printf("%d <-> ", ptr->no);
        ptr = ptr->next;
    }
    printf("NULL\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Doubly Linked List Menu ---");
        printf("\n1. Create List\n2. Insert Begin\n3. Insert End\n4. Insert at Position\n5. Delete Begin\n6. Delete End\n7. Display\n8. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_list(); break;
            case 2: insert_begin(); break;
            case 3: insert_end(); break;
            case 4: insert_pos(); break;
            case 5: delete_begin(); break;
            case 6: delete_end(); break;
            case 7: display(); break;
            case 8: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}