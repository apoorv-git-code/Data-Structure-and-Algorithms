#include <stdio.h>

// Function to perform Linear Search and return comparison count
int linearSearch(int arr[], int n, int target, int *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (arr[i] == target) return i;
    }
    return -1;
}

// Function for Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to perform Binary Search and return comparison count
int binarySearch(int arr[], int n, int target, int *comparisons) {
    int low = 0, high = n - 1;
    *comparisons = 0;
    while (low <= high) {
        (*comparisons)++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    int n, target, linearComp, binaryComp;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &target);

    // 1. Linear Search
    linearSearch(arr, n, target, &linearComp);
    printf("\n--- Linear Search ---\nComparisons: %d\n", linearComp);

    // 2. Sorting
    insertionSort(arr, n);
    printf("\nArray sorted using Insertion Sort.\n");

    // 3. Binary Search
    binarySearch(arr, n, target, &binaryComp);
    printf("\n--- Binary Search ---\nComparisons: %d\n", binaryComp);

    // 4. Comparison
    printf("\n--- Comparison ---\n");
    printf("Linear Search Comparisons: %d\n", linearComp);
    printf("Binary Search Comparisons: %d\n", binaryComp);

    return 0;
}