#include <stdio.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
    int arr[MAX];
    int front;
    int rear;
    int size;
} Deque;

void initDeque(Deque *dq) {
    dq->front = -1;
    dq->rear = 0;
    dq->size = 0;
}

bool isFull(Deque *dq) {
    return dq->size == MAX;
}

bool isEmpty(Deque *dq) {
    return dq->size == 0;
}

void insertFront(Deque *dq, int val) {
    if (isFull(dq)) {
        printf("Overflow\n");
        return;
    }
    if (dq->front == -1) { // First element
        dq->front = 0;
        dq->rear = 0;
    } else {
        // Circular wrap-around for front
        dq->front = (dq->front - 1 + MAX) % MAX;
    }
    dq->arr[dq->front] = val;
    dq->size++;
}

void insertRear(Deque *dq, int val) {
    if (isFull(dq)) {
        printf("Overflow\n");
        return;
    }
    if (dq->front == -1) {
        dq->front = 0;
        dq->rear = 0;
    } else {
        // Circular wrap-around for rear
        dq->rear = (dq->rear + 1) % MAX;
    }
    dq->arr[dq->rear] = val;
    dq->size++;
}

void deleteFront(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Underflow\n");
        return;
    }
    printf("Deleted from front: %d\n", dq->arr[dq->front]);
    dq->front = (dq->front + 1) % MAX;
    dq->size--;
}

void deleteRear(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Underflow\n");
        return;
    }
    printf("Deleted from rear: %d\n", dq->arr[dq->rear]);
    dq->rear = (dq->rear - 1 + MAX) % MAX;
    dq->size--;
}

int main() {
    Deque dq;
    initDeque(&dq);

    insertRear(&dq, 10);
    insertFront(&dq, 20);
    insertRear(&dq, 30);
    
    deleteFront(&dq);
    deleteRear(&dq);

    return 0;
}