#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node *next;
    struct Node *prev;
};

struct Node* createNode(int c, int e) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = c;
    newNode->exp = e;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

//inserting at the start
void insertAtBeginning(struct Node** head, int c, int e) {
    if (c == 0) return;
    struct Node* newNode = createNode(c, e);
    if (*head != NULL) {
        newNode->next = *head;

        (*head)->prev = newNode;
    }
    *head = newNode;
}

// deleting at the start when the pointer has been updated 
// Removes the current head and updates the next node's prev pointer.
void deleteAtBeginning(struct Node** head) {
    if (*head == NULL) return;
    
    struct Node* temp = *head;
    *head = (*head)->next;
    
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    
    free(temp);
    printf("Head node deleted successfully.\n");
}

// C/lear the whole list using delete_Beginning
void clearList(struct Node** head) {
    while (*head != NULL) {
        deleteAtBeginning(head);
    }
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        printf("(%dx^%d)", temp->coeff, temp->exp);
        temp = temp->next;
        if (temp != NULL) printf(" + ");
    }
    printf("\n");
}

// Addition/Subtraction logic
struct Node* operate(struct Node* P1, struct Node* P2, int isSubtraction) {
    struct Node* result = NULL;
    struct Node* t1 = P1;
    struct Node* t2 = P2;

    while (t1 != NULL || t2 != NULL) {
        int c;
        int e;

        if (t1 != NULL && (t2 == NULL || t1->exp < t2->exp)) { 
            // Note: < used here because InsertAtBeginning reverses input order
            c = t1->coeff; e = t1->exp;
            t1 = t1->next;
        } else if (t2 != NULL && (t1 == NULL || t2->exp < t1->exp)) {
            c = isSubtraction ? -t2->coeff : t2->coeff;
            e = t2->exp;
            t2 = t2->next;
        } else {
            c = isSubtraction ? (t1->coeff - t2->coeff) : (t1->coeff + t2->coeff);
            e = t1->exp;
            t1 = t1->next;
            t2 = t2->next;
        }
        
        if (c != 0) insertAtBeginning(&result, c, e);
    }
    return result;
}

struct Node* input() {
    struct Node* poly = NULL;
    int n, exp;
    int coeff;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    // User should enter terms in ASCENDING order for them to appear DESCENDING in display
    for (int i = 0; i < n; i++) {
        printf("Enter coeff and exp: ");
        scanf("%f %d", &coeff, &exp);
        insertAtBeginning(&poly, coeff, exp);
    }
    return poly;
}

int main() {
    struct Node *P1 = NULL, *P2 = NULL, *Result = NULL;
    int choice;

    while (1) {
        printf("\n1. Input\n2. Add\n3. Subtract\n4. Delete Head\n5. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearList(&P1); clearList(&P2);
                P1 = input(); P2 = input();
                break;
            case 2:
                clearList(&Result);
                Result = operate(P1, P2, 0);
                display(Result);
                break;
            case 3:
                clearList(&Result);
                Result = operate(P1, P2, 1);
                display(Result);
                break;
            case 4:
                deleteAtBeginning(&Result);
                display(Result);
                break;
            case 5:
                exit(0);
        }
    }
    return 0;
}