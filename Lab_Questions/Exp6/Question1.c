#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Node structure for the Doubly Linked List
struct Node {
    char data;
    struct Node* next;
    struct Node* prev;
};

// Deque structure
struct Deque {
    struct Node* front;
    struct Node* rear;
};

// Initialize Deque
void initDeque(struct Deque* dq) {
    dq->front = dq->rear = NULL;
}

// Input-restricted: Insert only at the Rear
void insertRear(struct Deque* dq, char ch) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = ch;
    newNode->next = NULL;
    newNode->prev = dq->rear;

    if (dq->rear == NULL) {
        dq->front = dq->rear = newNode;
    } else {
        dq->rear->next = newNode;
        dq->rear = newNode;
    }
}

// Delete from Front
char deleteFront(struct Deque* dq) {
    if (dq->front == NULL) return '\0';
    struct Node* temp = dq->front;
    char ch = temp->data;
    dq->front = dq->front->next;
    
    if (dq->front == NULL) dq->rear = NULL;
    else dq->front->prev = NULL;
    
    free(temp);
    return ch;
}

// Delete from Rear
char deleteRear(struct Deque* dq) {
    if (dq->rear == NULL) return '\0';
    struct Node* temp = dq->rear;
    char ch = temp->data;
    dq->rear = dq->rear->prev;
    
    if (dq->rear == NULL) dq->front = NULL;
    else dq->rear->next = NULL;
    
    free(temp);
    return ch;
}

// Logic to check if string is palindrome
bool isPalindrome(struct Deque* dq, int length) {
    // We only need to compare pairs length/2 times
    for (int i = 0; i < length / 2; i++) {
        if (deleteFront(dq) != deleteRear(dq)) {
            return false;
        }
    }
    return true;
}

int main() {
    struct Deque dq;
    initDeque(&dq);
    char str[100];

    printf("Enter a string: ");
    scanf("%s", str);

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        insertRear(&dq, str[i]);
    }

    if (isPalindrome(&dq, len)) {
        printf("The string \"%s\" is a palindrome.\n", str);
    } else {
        printf("The string \"%s\" is NOT a palindrome.\n", str);
    }

    return 0;
}