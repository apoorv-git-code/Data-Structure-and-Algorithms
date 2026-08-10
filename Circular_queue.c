// Static implementation of queue

//Convert this program to store sap id and name of a student 
#include <stdio.h>
#include <string.h>

#define SIZE 5

struct Student {
    int sap_id;
    char name[50];
};

struct Student queue[SIZE]; // Queue now stores Student objects
int front = -1, rear = -1;

void enqueue() {
    if ((rear + 1) % SIZE == front) {
        printf("Overflow... Queue is full.\n");
    } 
    else {
        rear = (rear + 1) % SIZE;       //Size was added due to rear condition wanting the code to be executed from the back
        
        printf("Enter SAP ID: ");
        scanf("%d", &queue[rear].sap_id);
        printf("Enter Student Name: ");
        scanf("%s", queue[rear].name); 

        if (front == -1) front = 0;
        printf("Student added successfully.\n");
    }
}

void dequeue() {
    if (front == -1) {
        printf("Underflow... Queue is empty.\n");
    } 
    else {
        printf("Deleted: [SAP ID: %d, Name: %s]\n", queue[front].sap_id, queue[front].name);
        
        if (front == rear) {            // Queue had only one element
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }
}

void display() {
    if (front == -1) {
        printf("Queue is empty.\n");
    } else {
        printf("\nStudents in Circular Queue\n");
        int i = front;
        while (1) {
            printf("SAP ID: %d | Name: %s\n", queue[i].sap_id, queue[i].name);
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Enqueue (Add Student)\n2. Dequeue (Remove Student)\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}

/*
// =========================================================================
// LINKED LIST IMPLEMENTATION OF CIRCULAR QUEUE
// =========================================================================

#include <stdlib.h>

// Note: To compile and run this instead of the array version, 
// uncomment this block and rename its 'main_ll' to 'main', 
// while commenting out or renaming the original array 'main' function.

struct Node {
    struct Student data;
    struct Node* next;
};

struct Node* front_ll = NULL;
struct Node* rear_ll = NULL;

void enqueue_ll() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Overflow...\n");
        return;
    }

    printf("Enter SAP ID: ");
    scanf("%d", &newNode->data.sap_id);
    printf("Enter Student Name: ");
    scanf("%s", newNode->data.name);

    if (front_ll == NULL) {
        front_ll = newNode;
    } else {
        rear_ll->next = newNode;
    }
    rear_ll = newNode;
    rear_ll->next = front_ll; // Make it circular

    printf("Student added successfully.\n");
}

void dequeue_ll() {
    if (front_ll == NULL) {
        printf("Underflow... Queue is empty.\n");
        return;
    }

    struct Node* temp = front_ll;
    printf("Deleted: [SAP ID: %d, Name: %s]\n", temp->data.sap_id, temp->data.name);

    if (front_ll == rear_ll) { // Only one element was present
        front_ll = NULL;
        rear_ll = NULL;
    } else {
        front_ll = front_ll->next;
        rear_ll->next = front_ll; // Maintain circular structure
    }

    free(temp);
}

void display_ll() {
    if (front_ll == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = front_ll;
    printf("\nStudents in Circular Queue (Linked List)\n");
    do {
        printf("SAP ID: %d | Name: %s\n", temp->data.sap_id, temp->data.name);
        temp = temp->next;
    } while (temp != front_ll);
}

int main_ll() {
    int choice;
    while (1) {
        printf("\n--- Linked List Circular Queue ---\n");
        printf("1. Enqueue (Add Student)\n2. Dequeue (Remove Student)\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: enqueue_ll(); break;
            case 2: dequeue_ll(); break;
            case 3: display_ll(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}
*/
