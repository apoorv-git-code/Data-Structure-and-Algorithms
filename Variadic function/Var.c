#include <stdio.h>
#include <stdarg.h> // Essential header

// 'count' is the fixed argument
int sum_numbers(int count, ...) {
    va_list args;           // 1. Declare the list
    int sum = 0;

    va_start(args, count);  // 2. Start at the first argument after 'count'

    for (int i = 0; i < count; i++) {
                                                       // 3. Fetch each argument as an 'int'
        sum += va_arg(args, int);
    }

    va_end(args);           // 4. Clean up
    return sum;
}

int main() {
    printf("Sum of 3 numbers: %d\n", sum_numbers(3, 10, 20, 30));
    printf("Sum of 5 numbers: %d\n", sum_numbers(5, 1, 2, 3, 4, 5));
    
    return 0;
}