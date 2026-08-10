#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// The "Abstract" type
typedef struct Stack Stack;

// The operations (The "What")
Stack* stack_create(int capacity);
void   stack_push(Stack* s, int value);
int    stack_pop(Stack* s);
bool   stack_is_empty(Stack* s);
void   stack_destroy(Stack* s);

#endif