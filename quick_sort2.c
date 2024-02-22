#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);
    int pivotValue = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[high]);
    
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivotValue) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        randomizedQuickSort(arr, low, pivotIndex - 1);
        randomizedQuickSort(arr, pivotIndex + 1, high);
    }
}

double measureTime(void (*sortingAlgorithm)(int[], int, int), int arr[], int arraySize) {
    clock_t start, end;
    start = clock();
    
    sortingAlgorithm(arr, 0, arraySize - 1);
    
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void generateRandomPermutation(int arr[], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        arr[i] = i;
    }
    
    for (int i = arraySize - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {
    srand(time(NULL));
    
    // Define locally
    int ARRAY_SIZE = 1000;
    int NUM_TESTS = 100000;
    
    int randomPermutation[ARRAY_SIZE];
    
    double averageTimeQuickSort = 0.0;
    double averageTimeRandomizedQuickSort = 0.0;
    
    for (int i = 0; i < NUM_TESTS; i++) {
        generateRandomPermutation(randomPermutation, ARRAY_SIZE);
        
        averageTimeQuickSort += measureTime(quickSort, randomPermutation, ARRAY_SIZE);
        averageTimeRandomizedQuickSort += measureTime(randomizedQuickSort, randomPermutation, ARRAY_SIZE);
    }
    
    averageTimeQuickSort /= NUM_TESTS;
    averageTimeRandomizedQuickSort /= NUM_TESTS;
    
    printf("Average running time for QuickSort: %f seconds\n", averageTimeQuickSort);
    printf("Average running time for Randomized QuickSort: %f seconds\n", averageTimeRandomizedQuickSort);
    
    return 0;
}
