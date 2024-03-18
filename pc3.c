#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* heap;
    int size;
    int capacity;
} MinPriorityQueue;

MinPriorityQueue* create(int capacity) {
    MinPriorityQueue* pq = (MinPriorityQueue*)malloc(sizeof(MinPriorityQueue));
    pq->heap = (int*)malloc(sizeof(int) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void insert(MinPriorityQueue* pq, int value) {
    pq->heap[pq->size++] = value;
    int i = pq->size - 1;
    while (i > 0 && pq->heap[i] < pq->heap[(i - 1) / 2]) {
        int temp = pq->heap[i];
        pq->heap[i] = pq->heap[(i - 1) / 2];
        pq->heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int deleteMin(MinPriorityQueue* pq) {
    if (pq->size == 0) return -1;
    int min = pq->heap[0];
    pq->heap[0] = pq->heap[--pq->size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < pq->size && pq->heap[left] < pq->heap[smallest]) smallest = left;
        if (right < pq->size && pq->heap[right] < pq->heap[smallest]) smallest = right;
        if (smallest != i) {
            int temp = pq->heap[i];
            pq->heap[i] = pq->heap[smallest];
            pq->heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return min;
}

void update(MinPriorityQueue* pq, int old_val, int new_val) {
    for (int i = 0; i < pq->size; ++i) {
        if (pq->heap[i] == old_val) {
            pq->heap[i] = new_val;
            while (i > 0 && pq->heap[i] < pq->heap[(i - 1) / 2]) {
                int temp = pq->heap[i];
                pq->heap[i] = pq->heap[(i - 1) / 2];
                pq->heap[(i - 1) / 2] = temp;
                i = (i - 1) / 2;
            }
            while (1) {
                int left = 2 * i + 1;
                int right = 2 * i + 2;
                int smallest = i;
                if (left < pq->size && pq->heap[left] < pq->heap[smallest]) smallest = left;
                if (right < pq->size && pq->heap[right] < pq->heap[smallest]) smallest = right;
                if (smallest != i) {
                    int temp = pq->heap[i];
                    pq->heap[i] = pq->heap[smallest];
                    pq->heap[smallest] = temp;
                    i = smallest;
                } else {
                    break;
                }
            }
            return;
        }
    }
    printf("%d not found in the priority queue.\n", old_val);
}

void display(MinPriorityQueue* pq) {
    printf("Min Priority Queue: ");
    for (int i = 0; i < pq->size; ++i) {
        printf("%d ", pq->heap[i]);
    }
    printf("\n");
}

int main() {
    MinPriorityQueue* pq = create(10);
    int choice, value, old_val, new_val;
    do {
        printf("\nMin Priority Queue Menu:\n");
        printf("1. Insert\n");
        printf("2. Delete Min\n");
        printf("3. Update\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insert(pq, value);
                break;
            case 2:
                value = deleteMin(pq);
                if (value != -1) printf("Deleted Min: %d\n", value);
                break;
            case 3:
                printf("Enter the old value to update: ");
                scanf("%d", &old_val);
                printf("Enter the new value: ");
                scanf("%d", &new_val);
                update(pq, old_val, new_val);
                break;
            case 4:
                display(pq);
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    free(pq->heap);
    free(pq);

    return 0;
}
