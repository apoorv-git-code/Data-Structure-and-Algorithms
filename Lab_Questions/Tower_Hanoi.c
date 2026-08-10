#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a stack
struct Stack {
    int capacity;
    int top;
    int *array;
    char name;
};

// Function to create a stack
struct Stack* createStack(int capacity, char name) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->name = name;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack operations
int isFull(struct Stack* stack) { return stack->top == stack->capacity - 1; }
int isEmpty(struct Stack* stack) { return stack->top == -1; }

void push(struct Stack* stack, int item) {
    if (isFull(stack)) return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) return -1;
    return stack->array[stack->top--];
}

// Function to show the current contents of a stack
void printStack(struct Stack* stack) {
    printf("%c: ", stack->name);
    if (isEmpty(stack)) {
        printf("Empty");
    } else {
        for (int i = 0; i <= stack->top; i++) {
            printf("%d ", stack->array[i]);
        }
    }
    printf("\n");
}

// Function to implement the movement between two poles
void moveDiskBetweenTwoPoles(struct Stack *src, struct Stack *dest) {
    int pole1TopDisk = pop(src);
    int pole2TopDisk = pop(dest);

    // When pole 1 is empty
    if (pole1TopDisk == -1) {
        push(src, pole2TopDisk);
        printf("Move disk %d from %c to %c\n", pole2TopDisk, dest->name, src->name);
    }
    // When pole 2 is empty
    else if (pole2TopDisk == -1) {
        push(dest, pole1TopDisk);
        printf("Move disk %d from %c to %c\n", pole1TopDisk, src->name, dest->name);
    }
    // When top disk of pole1 > top disk of pole2
    else if (pole1TopDisk > pole2TopDisk) {
        push(src, pole1TopDisk);
        push(src, pole2TopDisk);
        printf("Move disk %d from %c to %c\n", pole2TopDisk, dest->name, src->name);
    }
    // When top disk of pole1 < top disk of pole2
    else {
        push(dest, pole2TopDisk);
        push(dest, pole1TopDisk);
        printf("Move disk %d from %c to %c\n", pole1TopDisk, src->name, dest->name);
    }
}

void tohIterative(int n, struct Stack *src, struct Stack *aux, struct Stack *dest) {
    int i, total_moves;
    char s = 'S', d = 'D', a = 'A';

    // If n is even, swap destination and auxiliary
    if (n % 2 == 0) {
        struct Stack* temp = aux;
        aux = dest;
        dest = temp;
    }

    total_moves = pow(2, n) - 1;

    // Populating the source stack
    for (i = n; i >= 1; i--) push(src, i);

    printf("\nInitial state of all three stacks:\n");
    printStack(src); printStack(aux); printStack(dest);
    
    printf("\nTotal no. of moves expected: %d\n\n", total_moves);

    for (i = 1; i <= total_moves; i++) {
        if (i % 3 == 1)
            moveDiskBetweenTwoPoles(src, dest);
        else if (i % 3 == 2)
            moveDiskBetweenTwoPoles(src, aux);
        else if (i % 3 == 0)
            moveDiskBetweenTwoPoles(aux, dest);
    }
}

int main() {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Please enter a valid positive integer.\n");
        return 1;
    }

    struct Stack *src, *dest, *aux;
    src = createStack(n, 'S');
    aux = createStack(n, 'A');
    dest = createStack(n, 'D');

    tohIterative(n, src, aux, dest);

    printf("\nFinal state of all three stacks:\n");
    // Identifying stacks by original name for final print
    if (n % 2 == 0) {
        printStack(src); printStack(dest); printStack(aux);
    } else {
        printStack(src); printStack(aux); printStack(dest);
    }

    return 0;
}