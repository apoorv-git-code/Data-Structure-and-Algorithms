#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

void merge3Sorted(int arr[], int m) {
    int subSize = m / 3;
    int *result = (int *)malloc(m * sizeof(int));
    int i = 0, j = subSize, k = 2 * subSize;
    int idx = 0;

    while (idx < m) {
        int minVal = 2147483647;
        int choice = -1;

        if (i < subSize && arr[i] < minVal) { minVal = arr[i]; choice = 0; }
        if (j < 2 * subSize && arr[j] < minVal) { minVal = arr[j]; choice = 1; }
        if (k < m && arr[k] < minVal) { minVal = arr[k]; choice = 2; }

        result[idx++] = minVal;
        if (choice == 0) i++;
        else if (choice == 1) j++;
        else k++;
    }

    for (int n = 0; n < m; n++) arr[n] = result[n];
    free(result);
}

int main() {
    int m;
    printf("Enter array size (must be divisible by 3): ");
    scanf("%d", &m);

    if (m % 3 != 0) {
        printf("Error: Size must be divisible by 3.\n");
        return 1;
    }

    int arr[m];
    printf("Enter %d integers:\n", m);
    for (int i = 0; i < m; i++) scanf("%d", &arr[i]);

    printf("\n(a) Original array: ");
    printArray(arr, m);

    int subSize = m / 3;
    printf("\n(b) Subarrays before sorting:\n");
    for (int i = 0; i < 3; i++) {
        printf("Subarray %d: ", i + 1);
        printArray(&arr[i * subSize], subSize);
    }

    for (int i = 0; i < 3; i++) {
        bubbleSort(&arr[i * subSize], subSize);
    }

    printf("\n(c) Subarrays after Bubble Sort:\n");
    for (int i = 0; i < 3; i++) {
        printf("Subarray %d: ", i + 1);
        printArray(&arr[i * subSize], subSize);
    }

    merge3Sorted(arr, m);

    printf("\n(d) Final fully sorted array: ");
    printArray(arr, m);

    return 0;
}
