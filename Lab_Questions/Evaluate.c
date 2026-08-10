#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

typedef struct {
    double data[MAX];
    int top;
} Stack;

void push(Stack *s, double val) {
    if (s->top == MAX - 1) return;
    s->data[++(s->top)] = val;
}

double pop(Stack *s) {
    if (s->top == -1) return 0;
    return s->data[(s->top)--];
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

double evaluatePostfix(char* expr) {
    Stack s;
    s.top = -1;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            push(&s, expr[i] - '0');
        } else {
            double op2 = pop(&s);
            double op1 = pop(&s);
            push(&s, applyOp(op1, op2, expr[i]));
        }
    }
    return pop(&s);
}

double evaluatePrefix(char* expr) {
    Stack s;
    s.top = -1;
    int len = strlen(expr);
    for (int i = len - 1; i >= 0; i--) {
        if (isdigit(expr[i])) {
            push(&s, expr[i] - '0');
        } else {
            double op1 = pop(&s);
            double op2 = pop(&s);
            push(&s, applyOp(op1, op2, expr[i]));
        }
    }
    return pop(&s);
}

int main() {
    int choice;
    char expr[MAX];

    while (1) {
        printf("\n--- Expression Evaluator ---");
        printf("\n1. Evaluate Postfix (RPN)\n2. Evaluate Prefix (PN)\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        printf("Enter expression (single digits only): ");
        scanf("%s", expr);

        if (choice == 1)
            printf("Result: %.2f\n", evaluatePostfix(expr));
        else if (choice == 2)
            printf("Result: %.2f\n", evaluatePrefix(expr));
        else
            printf("Invalid choice!\n");
    }
    return 0;
}