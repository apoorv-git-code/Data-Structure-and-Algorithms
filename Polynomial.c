/* Use double linked list to reporesent polynomials other than the self referential elements each node should store the degree and the coefficients correspoding to the degree
perform addition and subtraction of these polynomials using a menu driven code
*/
/*polynomial addition*/
#include <stdio.h> 
#include <stdlib.h> 
 
struct node { 
    int data; 
    struct node* next; 
}; 
 
void insert(struct node** head, int value) { 
    struct node* newnode = (struct node*)malloc(sizeof(struct node)); 
    newnode->data = value; 
    newnode->next = NULL; 
 
    if (*head == NULL) { 
        *head = newnode; 
    } else { 
        struct node* temp = *head; 
        while (temp->next != NULL) 
            temp = temp->next; 
        temp->next = newnode; 
    } 
} 
 
void display(struct node* head) { 
    int power = 2; 
    while (head != NULL) { 
        if (power > 0) 
            printf("%dx^%d ", head->data, power); 
        else 
            printf("%d ", head->data); 
 
        if (head->next != NULL) 
            printf("+ "); 
 
        head = head->next; 
        power--; 
    } 
    printf("\n"); 
} 
 
int main() { 
    struct node *head1 = NULL, *head2 = NULL, *head3 = NULL; 
    int value; 
 
    printf("Enter coefficients for first polynomial (ax^2 + bx + c):\n"); 
    for (int i = 0; i < 3; i++) { 
        scanf("%d", &value); 
        insert(&head1, value); 
    } 
 
    printf("Enter coefficients for second polynomial (ax^2 + bx + c):\n"); 
    for (int i = 0; i < 3; i++) { 
        scanf("%d", &value); 
        insert(&head2, value); 
    } 
 
    struct node *p = head1, *q = head2; 
 
    while (p != NULL && q != NULL) { 
        insert(&head3, p->data + q->data); 
        p = p->next; 
        q = q->next; 
    } 
 
    printf("\nFirst Polynomial: "); 
    display(head1); 
 
    printf("Second Polynomial: "); 
    display(head2); 
 
    printf("Sum Polynomial: "); 
    display(head3); 
 
    return 0; 
}
