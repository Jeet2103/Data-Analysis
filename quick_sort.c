#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int low, int high, int pivotChoice, int* comparisons) {
    int pivot;

    switch (pivotChoice) {
        case 1:
            pivot = arr[low];
            break;
        case 2:
            pivot = arr[high];
            break;
        case 3:
            pivot = arr[low + rand() % (high - low + 1)];
            break;
    }

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++; // Increment comparisons counter
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

void quicksort(int arr[], int low, int high, int pivotChoice, int* comparisons) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, pivotChoice, comparisons);

        quicksort(arr, low, pivotIndex - 1, pivotChoice, comparisons);
        quicksort(arr, pivotIndex + 1, high, pivotChoice, comparisons);
    }
}

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
        quicksort(arr_copy, 0, size - 1, pivotChoice, &comparisons);
        end = clock();
        // printf("The size is : %d\n",size);
        printf("Using pivot choice %d:\n", pivotChoice);
        printf("Comparisons: %d\n", comparisons);
        printf("Time taken: %f seconds\n", ((double)end - start) / CLOCKS_PER_SEC);

        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    int sizes[] = {10000, 100000, 1000000};

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int arr[sizes[i]];
        for (int j = 0; j < sizes[i]; j++) {
            arr[j] = rand();
        }

        estimateComparisons(arr, sizes[i]);
    }

    return 0;
}
