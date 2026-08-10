#include <stdio.h>

void findKthSmallest(int arr[], int n, int k) {
    // Perform only k passes of selection sort
    for (int i = 0; i < k; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Swap the found minimum element with the element at index i
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }

    printf("The %dth smallest element is: %d\n", k, arr[k - 1]);
}

int main() {
    int n, k;

    printf("Enter the number of elements (n): ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d array elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    if (k > n || k <= 0) {
        printf("Invalid value of k. Please enter k between 1 and %d.\n", n);
    } else {
        findKthSmallest(arr, n, k);
    }

    return 0;
}
