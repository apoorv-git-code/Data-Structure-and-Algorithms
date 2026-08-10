#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

/* ========================================================
   1. STACK STRUCTURES & FUNCTIONS
   ======================================================== */

// Stack for Characters (Operators/Brackets)
struct CharNode {
    char data;
    struct CharNode* next;
};
struct CharNode* charTop = NULL;

void pushChar(char x) {
    struct CharNode* newNode = (struct CharNode*)malloc(sizeof(struct CharNode));
    if (!newNode) return;
    newNode->data = x;
    newNode->next = charTop;
    charTop = newNode;
}

char popChar() {
    if (charTop == NULL) return '\0';
    struct CharNode* temp = charTop;
    char val = temp->data;
    charTop = charTop->next;
    free(temp);
    return val;
}

char peekChar() {
    return (charTop == NULL) ? '\0' : charTop->data;
}

// Stack for Integers (Math Evaluation)
struct IntNode {
    int data;
    struct IntNode* next;
};

void pushInt(struct IntNode** top, int value) {
    struct IntNode* newNode = (struct IntNode*)malloc(sizeof(struct IntNode));
    if (!newNode) return;
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}

int popInt(struct IntNode** top) {
    if (*top == NULL) return 0;
    struct IntNode* temp = *top;
    int val = temp->data;
    *top = (*top)->next;
    free(temp);
    return val;
}

/* ========================================================
   2. HELPER FUNCTIONS
   ======================================================== */

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; //include all operators  relational etc
    return 0;
}

void reverse(char exp[]) {
    int len = strlen(exp);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
    }
}

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b == 0) ? 0 : a / b;
        case '^': return (int)pow(a, b);
        default: return 0;
    }
}

/* ========================================================
   3. CONVERSION LOGIC (INFIX TO POSTFIX & PREFIX)
   ======================================================== */

void infixToPostfix(char infix[], char postfix[]) {
    int j = 0;
    charTop = NULL; // Reset global stack
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            pushChar(ch);
        } else if (ch == ')') {
            while (peekChar() != '(') postfix[j++] = popChar();
            popChar();
        } else {
            while (charTop != NULL && precedence(peekChar()) >= precedence(ch))
                postfix[j++] = popChar();
            pushChar(ch);
        }
    }
    while (charTop != NULL) postfix[j++] = popChar();
    postfix[j] = '\0';
}

void infixToPrefix(char infix[], char prefix[]) {
    char temp[MAX_SIZE];
    strcpy(temp, infix);
    reverse(temp);
    for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] == '(') temp[i] = ')';
        else if (temp[i] == ')') temp[i] = '(';
    }
    
    int j = 0;
    charTop = NULL;
    for (int i = 0; temp[i] != '\0'; i++) {
        char ch = temp[i];
        if (isalnum(ch)) {
            prefix[j++] = ch;
        } else if (ch == '(') {
            pushChar(ch);
        } else if (ch == ')') {
            while (peekChar() != '(') prefix[j++] = popChar();
            popChar();
        } else {
            while (charTop != NULL && precedence(peekChar()) > precedence(ch))
                prefix[j++] = popChar();
            pushChar(ch);
        }
    }
    while (charTop != NULL) prefix[j++] = popChar();
    prefix[j] = '\0';
    reverse(prefix);
}

/* ========================================================
   4. MENU Driven Code
   ======================================================== */

int main() {
    char infix[MAX_SIZE], result[MAX_SIZE];
    int choice;

    while (1) {
        printf("\n--- MATH EXPRESSION SYSTEM ---\n");
        printf("1. Infix to Prefix (Conversion)\n");
        printf("2. Infix to Postfix (Conversion )\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        printf("Enter Infix: ");
        scanf("%s", infix);

        if (choice == 1) {
            infixToPrefix(infix, result);
            printf("Prefix: %s\n", result);
        } else if (choice == 2) {
            infixToPostfix(infix, result);
            printf("Postfix: %s\n", result);
        }
    }
    return 0;
}