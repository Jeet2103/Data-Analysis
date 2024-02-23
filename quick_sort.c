#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements in an array
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high, int* comparisons) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*comparisons)++; // Increment comparisons for each comparison made

        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

// Function to implement QuickSort using the first element as the pivot
void quickSortFirstPivot(int arr[], int low, int high, int* comparisons) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, comparisons);

        quickSortFirstPivot(arr, low, pivotIndex - 1, comparisons);
        quickSortFirstPivot(arr, pivotIndex + 1, high, comparisons);
    }
}

// Function to implement QuickSort using the last element as the pivot
void quickSortLastPivot(int arr[], int low, int high, int* comparisons) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, comparisons);

        quickSortLastPivot(arr, low, pivotIndex - 1, comparisons);
        quickSortLastPivot(arr, pivotIndex + 1, high, comparisons);
    }
}

// Function to implement QuickSort using a randomly chosen element as the pivot
void quickSortRandomPivot(int arr[], int low, int high, int* comparisons) {
    if (low < high) {
        // Choose a random index as the pivot
        int randomIndex = low + rand() % (high - low + 1);
        swap(&arr[randomIndex], &arr[high]);

        int pivotIndex = partition(arr, low, high, comparisons);

        quickSortRandomPivot(arr, low, pivotIndex - 1, comparisons);
        quickSortRandomPivot(arr, pivotIndex + 1, high, comparisons);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size = 10;
    int arrAscending[size];
    int arrDescending[size];
    int arrRandom[size];

    // Case 1: Array sorted in ascending order (1 to 10)
    for (int i = 0; i < size; i++) {
        arrAscending[i] = i + 1;
    }

    // Case 2: Array sorted in descending order (10 to 1)
    for (int i = 0; i < size; i++) {
        arrDescending[i] = size - i;
    }

    // Case 3: Randomly generated array
    for (int i = 0; i < size; i++) {
        arrRandom[i] = rand() % 100; // Limiting values to ease readability
    }

    // Perform QuickSort for each case and each pivot choice

    // Case 1: Array sorted in ascending order
    printf("Original Array (Ascending Order): ");
    printArray(arrAscending, size);

    int comparisonsAscFirstPivot = 0;
    quickSortFirstPivot(arrAscending, 0, size - 1, &comparisonsAscFirstPivot);
    printf("Sorted Array (First Pivot): ");
    printArray(arrAscending, size);
    printf("Comparisons: %d\n", comparisonsAscFirstPivot);

    int comparisonsAscLastPivot = 0;
    quickSortLastPivot(arrAscending, 0, size - 1, &comparisonsAscLastPivot);
    printf("Sorted Array (Last Pivot): ");
    printArray(arrAscending, size);
    printf("Comparisons: %d\n", comparisonsAscLastPivot);

    int comparisonsAscRandomPivot = 0;
    quickSortRandomPivot(arrAscending, 0, size - 1, &comparisonsAscRandomPivot);
    printf("Sorted Array (Random Pivot): ");
    printArray(arrAscending, size);
    printf("Comparisons: %d\n", comparisonsAscRandomPivot);

    printf("\n");

    // Case 2: Array sorted in descending order
    printf("Original Array (Descending Order): ");
    printArray(arrDescending, size);

    int comparisonsDescFirstPivot = 0;
    quickSortFirstPivot(arrDescending, 0, size - 1, &comparisonsDescFirstPivot);
    printf("Sorted Array (First Pivot): ");
    printArray(arrDescending, size);
    printf("Comparisons: %d\n", comparisonsDescFirstPivot);

    int comparisonsDescLastPivot = 0;
    quickSortLastPivot(arrDescending, 0, size - 1, &comparisonsDescLastPivot);
    printf("Sorted Array (Last Pivot): ");
    printArray(arrDescending, size);
    printf("Comparisons: %d\n", comparisonsDescLastPivot);

    int comparisonsDescRandomPivot = 0;
    quickSortRandomPivot(arrDescending, 0, size - 1, &comparisonsDescRandomPivot);
    printf("Sorted Array (Random Pivot): ");
    printArray(arrDescending, size);
    printf("Comparisons: %d\n", comparisonsDescRandomPivot);

    printf("\n");

    // Case 3: Randomly generated array
    printf("Original Array (Randomly Generated): ");
    printArray(arrRandom, size);

    int comparisonsRandomFirstPivot = 0;
    quickSortFirstPivot(arrRandom, 0, size - 1, &comparisonsRandomFirstPivot);
    printf("Sorted Array (First Pivot): ");
    printArray(arrRandom, size);
    printf("Comparisons: %d\n", comparisonsRandomFirstPivot);

    int comparisonsRandomLastPivot = 0;
    quickSortLastPivot(arrRandom, 0, size - 1, &comparisonsRandomLastPivot);
    printf("Sorted Array (Last Pivot): ");
    printArray(arrRandom, size);
    printf("Comparisons: %d\n", comparisonsRandomLastPivot);

    int comparisonsRandomRandomPivot = 0;
    quickSortRandomPivot(arrRandom, 0, size - 1, &comparisonsRandomRandomPivot);
    printf("Sorted Array (Random Pivot): ");
    printArray(arrRandom, size);
    printf("Comparisons: %d\n", comparisonsRandomRandomPivot);

    return 0;
}
