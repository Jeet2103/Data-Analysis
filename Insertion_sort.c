#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Insertion Sort and count comparisons
int insertionSort(int arr[], int n) {
    int comparisons = 0;

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        comparisons++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }

        arr[j + 1] = key;
        for(int j=0;j<n;j++)
        {
            printf("%d  ",arr[j]);
        }
        printf("\n");
    }

    return comparisons;
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int *arr_desired = (int *)malloc(10 * sizeof(int));
    int *arr_reverse = (int *)malloc(10 * sizeof(int));
    int *arr_random = (int *)malloc(10 * sizeof(int));

    // i) Elements arranged in the desired order
    printf("Case i: Elements in desired order\n");
    for (int i = 0; i < 10; ++i) {
        arr_desired[i] = i + 1;
    }
    printArray(arr_desired, 10);
    int comparisons_desired = insertionSort(arr_desired, 10);
    printf("Comparisons: %d\n\n", comparisons_desired);

    // ii) Elements arranged in completely reverse order
    printf("Case ii: Elements in completely reverse order\n");
    for (int i = 0; i < 10; ++i) {
        arr_reverse[i] = 10 - i;
    }
    printArray(arr_reverse, 10);
    int comparisons_reverse = insertionSort(arr_reverse, 10);
    printf("Comparisons: %d\n\n", comparisons_reverse);

    // iii) Elements randomly generated
    printf("Case iii: Elements randomly generated\n");
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        arr_random[i] = rand() % 100; // assuming elements are within the range [0, 99]
    }
    printArray(arr_random, 10);
    int comparisons_random = insertionSort(arr_random, 10);
    printf("Comparisons: %d\n\n", comparisons_random);

    // Free dynamically allocated memory
    free(arr_desired);
    free(arr_reverse);
    free(arr_random);

    return 0;
}
