// Call by value
#include <stdio.h>

void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    // Changes only happen here inside the function
}

int main() {
    int x = 10, y = 20;
    swapByValue(x, y);
    printf("Call by Value: x = %d, y = %d\n", x, y); 
    // Output will still be 10, 20
    return 0;
}

// Call by reference

#include <stdio.h>

// Function takes pointers as arguments
void swapByReference(int *a, int *b) {
    int temp = *a; // temp = value at address a
    *a = *b;       // value at address a = value at address b
    *b = temp;     // value at address b = temp
}

int main() {
    int x = 10, y = 20;
    // Pass the addresses of x and y using '&'
    swapByReference(&x, &y);
    printf("Call by Reference: x = %d, y = %d\n", x, y); 
    // Output will be 20, 10
    return 0;
}