#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    long long int phone;
    char name[50];
    int status; // 0: Empty, 1: Occupied, -1: Deleted
} Contact;

typedef struct {
    Contact *table;
    int size;
    int count;
} Phonebook;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Find the next prime number approximately 2 * current size
int nextPrime(int n) {
    int next = 2 * n + 1;
    while (!isPrime(next)) next++;
    return next;
}

// Hash function: sum of digits % size
int hashFunction(long long int phone, int size) {
    int sum = 0;
    long long int temp = phone;
    while (temp > 0) {
        sum += (temp % 10);
        temp /= 10;
    }
    return sum % size;
}

Phonebook* createTable(int size) {
    Phonebook *pb = (Phonebook*)malloc(sizeof(Phonebook));
    pb->size = size;
    pb->count = 0;
    pb->table = (Contact*)malloc(size * sizeof(Contact));
    for (int i = 0; i < size; i++) {
        pb->table[i].status = 0; // Initialize as Empty
    }
    return pb;
}

void insert(Phonebook *pb, long long int phone, char name[]);

// Rehashing function
void rehash(Phonebook *pb) {
    int oldSize = pb->size;
    Contact *oldTable = pb->table;

    pb->size = nextPrime(oldSize);
    pb->table = (Contact*)malloc(pb->size * sizeof(Contact));
    pb->count = 0;

    for (int i = 0; i < pb->size; i++) pb->table[i].status = 0;

    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].status == 1) {
            insert(pb, oldTable[i].phone, oldTable[i].name);
        }
    }
    free(oldTable);
    printf("\n--- Table resized to %d ---\n", pb->size);
}

void insert(Phonebook *pb, long long int phone, char name[]) {
    // Check Load Factor
    if ((float)pb->count / pb->size > 0.7) {
        rehash(pb);
    }

    int index = hashFunction(phone, pb->size);
    int i = 0, pos;

    while (i < pb->size) {
        pos = (index + i) % pb->size;
        
        // If phone already exists, update and return
        if (pb->table[pos].status == 1 && pb->table[pos].phone == phone) {
            strcpy(pb->table[pos].name, name);
            return;
        }
        
        // Find first Empty or Deleted slot
        if (pb->table[pos].status <= 0) {
            pb->table[pos].phone = phone;
            strcpy(pb->table[pos].name, name);
            pb->table[pos].status = 1;
            pb->count++;
            return;
        }
        i++;
    }
}

void search(Phonebook *pb, long long int phone) {
    int index = hashFunction(phone, pb->size);
    for (int i = 0; i < pb->size; i++) {
        int pos = (index + i) % pb->size;
        if (pb->table[pos].status == 0) break; // Stop if Empty
        if (pb->table[pos].status == 1 && pb->table[pos].phone == phone) {
            printf("Found: %s (%lld)\n", pb->table[pos].name, pb->table[pos].phone);
            return;
        }
    }
    printf("Contact not found.\n");
}

void deleteContact(Phonebook *pb, long long int phone) {
    int index = hashFunction(phone, pb->size);
    for (int i = 0; i < pb->size; i++) {
        int pos = (index + i) % pb->size;
        if (pb->table[pos].status == 0) break;
        if (pb->table[pos].status == 1 && pb->table[pos].phone == phone) {
            pb->table[pos].status = -1; // Mark as Deleted
            pb->count--;
            printf("Contact %lld deleted.\n", phone);
            return;
        }
    }
    printf("Contact not found to delete.\n");
}

void display(Phonebook *pb) {
    printf("\n--- Phonebook Table ---\n");
    for (int i = 0; i < pb->size; i++) {
        if (pb->table[i].status == 0) printf("[%d] EMPTY\n", i);
        else if (pb->table[i].status == -1) printf("[%d] DELETED\n", i);
        else printf("[%d] (%lld, %s)\n", i, pb->table[i].phone, pb->table[i].name);
    }
}

int main() {
    Phonebook *pb = createTable(7); // Initial prime size
    
    insert(pb, 9876543210LL, "Apoorv");
    insert(pb, 8765432109LL, "Bhoovi");
    insert(pb, 7654321098LL, "Chardiwari");
    insert(pb, 6543210987LL, "Hardik");
    insert(pb, 5432109876LL, "Jiya"); // This will trigger rehash (5/7 > 0.7)

    display(pb);
    search(pb, 8765432109LL);
    deleteContact(pb, 8765432109LL);
    display(pb);

    return 0;
}