#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;

Product cart[MAX_ITEMS];
int count = 0;

void addItem() {
    if (count >= MAX_ITEMS) {
        printf("Cart is full!\n");
        return;
    }
    printf("Enter ID, Name, Price, Quantity: ");
    scanf("%d %s %f %d", &cart[count].id, cart[count].name, &cart[count].price, &cart[count].quantity);
    count++;
    printf("Item added successfully.\n");
}

void displayCart() {
    printf("\n--- Shopping Cart ---\n");
    printf("ID\tName\tPrice\tQty\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%.2f\t%d\n", cart[i].id, cart[i].name, cart[i].price, cart[i].quantity);
    }
}

void updateItem() {
    int id, found = 0;
    printf("Enter Product ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (cart[i].id == id) {
            printf("Enter new Price and Quantity: ");
            scanf("%f %d", &cart[i].price, &cart[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found){
        printf("Item not found.\n");
    }
}

void deleteItem() {
    int id, found = 0;
    printf("Enter Product ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (cart[i].id == id) {
            for (int j = i; j < count - 1; j++) 
            cart[j] = cart[j + 1];
            count--;
            found = 1;
            printf("Item deleted.\n");
            break;
        }
    }
    if (!found) printf("Item not found.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n ------ Menu Driven Program for Shopping Cart ------\n");
        printf("\n Choose which operation to be performed from below:");
        printf("\n1. Add\n2. View\n3. Update\n4. Delete\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addItem(); 
                    break;
            case 2: displayCart(); 
                    break;
            case 3: updateItem();
                    break;
            case 4: deleteItem(); 
                    break;
            case 5: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}