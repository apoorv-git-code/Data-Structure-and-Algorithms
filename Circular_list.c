#include<stdio.h> 
#include<stdlib.h> 
#include<math.h> 
int count=0;   
struct node   
{ 
int no;   
struct node *next; 
//To count no. of nodes in list 
//Define structure of a node   
//data element 
//Self-Referential Element (SRE) 
}*new, *ptr, *temp, *first=NULL; 
void get_element()  
{ 
//create a new node & store data 
if(first == NULL)  
printf("List is created now. It contains one node.\n"); 
new = (struct node*) malloc(sizeof(struct node)); 
if(new!=NULL) 
{ 
printf("New Address: %p\n", new); 
printf("Enter data to insert: "); 
scanf("%d", &new->no);   
new->next=NULL;          
} 
else printf("\nDMA unsuccessful. Try again later."); 
} 
void insert_end() 
{ 
get_element();    
count = count+1; 
//traverse to end of list  
for(ptr=first; ptr->next!=NULL; ptr=ptr->next);  
ptr->next=new;     
printf("Element inserted in List.\n");  
