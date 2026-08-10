#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Push element onto stack
void push(char item) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = item;
    }
}

// Pop element from stack
char pop() {
    if (top == -1) {
        return -1;
    } else {
        return stack[top--];
    }
}

// Determine operator precedence
int precedence(char symbol) {
    if (symbol == '^') {
        return 3;
    } else if (symbol == '*' || symbol == '/') {
        return 2;
    } else if (symbol == '+' || symbol == '-') {
        return 1;
    } else {
        return 0;
    }
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char item, x;

    push('(');          // Push "(" to stack
    strcat(infix, ")"); // Add ")" to end of infix expression

    for (i = 0; infix[i] != '\0'; i++) {
        item = infix[i];

        if (item == '(') {
            push(item);
        } 
        else if (isalnum(item)) {
            postfix[j++] = item; // Add operand to output
        } 
        else if (item == ')') {
            x = pop();
            while (x != '(') {
                postfix[j++] = x;
                x = pop();
            }
        } 
        else { // If operator
            while (precedence(stack[top]) >= precedence(item)) {
                postfix[j++] = pop();
            }
            push(item);
        }
    }
    postfix[j] = '\0'; // Null-terminate the string
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter Infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}