#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform the partition step of the quicksort algorithm
int partition(int arr[], int low, int high, int pivotChoice) {
    int pivot;

    // Choose pivot based on the specified strategy
    switch (pivotChoice) {
        case 1: // First element
            pivot = arr[low];
            break;
        case 2: // Middle element
            pivot = arr[(low + high) / 2];
            break;
        case 3: // Random element
            pivot = arr[low + rand() % (high - low + 1)];
            break;
        default: // Default to last element
            pivot = arr[high];
    }

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap arr[i+1] and arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// Function to perform the quicksort algorithm
void quicksort(int arr[], int low, int high, int pivotChoice) {
    if (low < high) {
        // Find the partitioning index
        int pivotIndex = partition(arr, low, high, pivotChoice);

        // Recursively sort the sub-arrays
        quicksort(arr, low, pivotIndex - 1, pivotChoice);
        quicksort(arr, pivotIndex + 1, high, pivotChoice);
    }
}

// Function to estimate the number of comparisons for different pivots
void estimateComparisons(int arr[], int size) {
    printf("Input size: %d\n", size);

    for (int pivotChoice = 1; pivotChoice <= 3; pivotChoice++) {
        int arr_copy[size];
        for (int i = 0; i < size; i++) {
            arr_copy[i] = arr[i];
        }

        int comparisons = 0;
        clock_t start, end;
        start = clock();
        quicksort(arr_copy, 0, size - 1, pivotChoice);
        end = clock();
        comparisons = size - 1;

        printf("Using pivot choice %d:\n", pivotChoice);
        printf("Comparisons: %d\n", comparisons);
        printf("Time taken: %f seconds\n", ((double)end - start) / CLOCKS_PER_SEC);

        printf("\n");
    }
}

int main() {
    // Seed for randomization
    srand(time(NULL));

    // Set the input sizes
    int sizes[] = {10000, 100000, 1000000};

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        // Generate random array for each input size
        int arr[sizes[i]];
        for (int j = 0; j < sizes[i]; j++) {
            arr[j] = rand();
        }

        // Estimate the number of comparisons for different pivot choices
        estimateComparisons(arr, sizes[i]);
    }

    return 0;
}
