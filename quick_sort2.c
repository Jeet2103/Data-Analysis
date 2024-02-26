#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to generate a random permutation of the first n natural numbers
void Generate_random_sequence(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    FILE *fp = fopen("unsorted_seq.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    // Generate the sequence
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;

    // Shuffle the sequence
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }

    // Write the shuffled sequence to the file
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", arr[i]);

    fclose(fp);
    free(arr);
}

// Randomized Partition function for QuickSort
int randomized_partition(int arr[], int left, int right) {
    srand(time(NULL));
    int random = left + rand() % (right - left + 1); // Random pivot index
    swap(&arr[random], &arr[right]); // Swap random pivot with the last element

    int pivot = arr[right]; // Pivot element
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

// Randomized QuickSort function
void Randomized_quick_sort(int arr[], int left, int right) {
    if (left < right) {
        int pi = randomized_partition(arr, left, right); // Partitioning index
        Randomized_quick_sort(arr, left, pi - 1);
        Randomized_quick_sort(arr, pi + 1, right);
    }
}

int main() {
    int n = 1000;
    Generate_random_sequence(n);
    printf("Random permutation of first %d natural numbers generated and stored in unsorted_seq.txt.\n", n);
    FILE *fp = fopen("unsorted_seq.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
    fclose(fp);

    Randomized_quick_sort(arr, 0, n - 1);

    printf("Sorted sequence: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}