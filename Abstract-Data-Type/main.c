#include <stdio.h>
#include "stack.h"

int main() {
    Stack* myStack = stack_create(10);

    stack_push(myStack, 42);
    stack_push(myStack, 100);

    printf("Popped: %d\n", stack_pop(myStack)); // 100
    
    // myStack->top = 0; // ERROR: Compiler doesn't know what 'top' is here!

    stack_destroy(myStack);
    return 0;
}