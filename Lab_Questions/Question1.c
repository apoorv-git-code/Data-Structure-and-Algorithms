// Displaying the contents of the linked list in reverse order 
#include<stdio.h>
#include<stdlib.h>
int count=0;			//To count no. of nodes in list

struct node			//Define the structure of a node
{
	int no;			//data element of a node
	struct node *next;	//self-referential element of a node
}*new, *first=NULL, *ptr;

struct node* reverseList(struct node* first) {
    struct node *prev = NULL, *current = first, *next = NULL;

    while (current != NULL) {
        next = current->next;    // 1. Save the next node
        current->next = prev;    // 2. Reverse the pointer
        prev = current;          // 3. Move prev forward
        current = next;          // 4. Move current forward
    }
    return prev; // 'prev' is the new first
}


