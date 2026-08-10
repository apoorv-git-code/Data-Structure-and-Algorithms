#include <stdlib.h>
#include "stack.h"

struct Stack {
    int* data;
    int top;
    int capacity;
};

Stack* stack_create(int capacity) {
    Stack* s = malloc(sizeof(Stack));
    s->data = malloc(sizeof(int) * capacity);
    s->top = -1;
    s->capacity = capacity;
    return s;
}

void stack_push(Stack* s, int value) {
    if (s->top < s->capacity - 1) {
        s->data[++(s->top)] = value;
    }
}

int stack_pop(Stack* s) {
    if (!stack_is_empty(s)) {
        return s->data[(s->top)--];
    }
    return -1; // Error value
}

bool stack_is_empty(Stack* s) {
    return s->top == -1;
}

void stack_destroy(Stack* s) {
    free(s->data);
    free(s);
}