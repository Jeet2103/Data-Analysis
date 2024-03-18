#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the min-heap
typedef struct
{
    int *heap;
    int size;
    int capacity;
} MinPriorityQueue;

// Function prototypes
MinPriorityQueue *createMinPriorityQueue(int capacity);
void insert(MinPriorityQueue *pq, int value);
int deleteMin(MinPriorityQueue *pq);
void update(MinPriorityQueue *pq, int old_value, int new_value);
void display(MinPriorityQueue *pq);

int main()
{
    MinPriorityQueue *priorityQueue = createMinPriorityQueue(10);
    int choice, value, old_value, new_value;

    do
    {
        printf("\nMin Priority Queue Menu:\n");
        printf("1. Insert\n");
        printf("2. Delete Min\n");
        printf("3. Update\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the value to insert: ");
            scanf("%d", &value);
            insert(priorityQueue, value);
            break;

        case 2:
            value = deleteMin(priorityQueue);
            if (value != -1)
            {
                printf("Deleted Min: %d\n", value);
            }
            break;

        case 3:
            printf("Enter the old value to update: ");
            scanf("%d", &old_value);
            printf("Enter the new value: ");
            scanf("%d", &new_value);
            update(priorityQueue, old_value, new_value);
            break;

        case 4:
            display(priorityQueue);
            break;

        case 5:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    free(priorityQueue->heap);
    free(priorityQueue);

    return 0;
}

// Function to create a new min priority queue
MinPriorityQueue *createMinPriorityQueue(int capacity)
{
    MinPriorityQueue *pq = (MinPriorityQueue *)malloc(sizeof(MinPriorityQueue));
    pq->heap = (int *)malloc(sizeof(int) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

// Function to insert a new element into the min priority queue
void insert(MinPriorityQueue *pq, int value)
{
    if (pq->size == pq->capacity)
    {
        printf("Priority Queue is full. Cannot insert %d\n", value);
        return;
    }

    // Insert the new element at the end of the heap
    pq->heap[pq->size] = value;
    pq->size++;

    // Restore the min-heap property
    int current_index = pq->size - 1;
    while (current_index > 0)
    {
        int parent_index = (current_index - 1) / 2;
        if (pq->heap[current_index] < pq->heap[parent_index])
        {
            // Swap the current element with its parent
            int temp = pq->heap[current_index];
            pq->heap[current_index] = pq->heap[parent_index];
            pq->heap[parent_index] = temp;

            current_index = parent_index;
        }
        else
        {
            break;
        }
    }
}

// Function to delete the minimum element from the min priority queue
int deleteMin(MinPriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("Priority Queue is empty. Cannot delete.\n");
        return -1; // Indicates an error
    }

    // Swap the root (minimum element) with the last element
    int min_value = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    // Restore the min-heap property
    int current_index = 0;
    while (1)
    {
        int left_child_index = 2 * current_index + 1;
        int right_child_index = 2 * current_index + 2;
        int smallest = current_index;

        if (left_child_index < pq->size && pq->heap[left_child_index] < pq->heap[smallest])
        {
            smallest = left_child_index;
        }

        if (right_child_index < pq->size && pq->heap[right_child_index] < pq->heap[smallest])
        {
            smallest = right_child_index;
        }

        if (smallest != current_index)
        {
            // Swap the current element with the smallest child
            int temp = pq->heap[current_index];
            pq->heap[current_index] = pq->heap[smallest];
            pq->heap[smallest] = temp;

            current_index = smallest;
        }
        else
        {
            break;
        }
    }

    return min_value;
}

// Function to update the priority of an element in the min priority queue
void update(MinPriorityQueue *pq, int old_value, int new_value)
{
    for (int i = 0; i < pq->size; i++)
    {
        if (pq->heap[i] == old_value)
        {
            pq->heap[i] = new_value;

            // Adjust the heap to maintain the min-heap property
            int current_index = i;
            while (current_index > 0)
            {
                int parent_index = (current_index - 1) / 2;
                if (pq->heap[current_index] < pq->heap[parent_index])
                {
                    // Swap the current element with its parent
                    int temp = pq->heap[current_index];
                    pq->heap[current_index] = pq->heap[parent_index];
                    pq->heap[parent_index] = temp;

                    current_index = parent_index;
                }
                else
                {
                    break;
                }
            }

            // Check if the update requires moving the element down the heap
            while (1)
            {
                int left_child_index = 2 * current_index + 1;
                int right_child_index = 2 * current_index + 2;
                int smallest = current_index;

                if (left_child_index < pq->size && pq->heap[left_child_index] < pq->heap[smallest])
                {
                    smallest = left_child_index;
                }

                if (right_child_index < pq->size && pq->heap[right_child_index] < pq->heap[smallest])
                {
                    smallest = right_child_index;
                }

                if (smallest != current_index)
                {
                    // Swap the current element with the smallest child
                    int temp = pq->heap[current_index];
                    pq->heap[current_index] = pq->heap[smallest];
                    pq->heap[smallest] = temp;

                    current_index = smallest;
                }
                else
                {
                    break;
                }
            }

            return;
        }
    }

    printf("%d not found in the priority queue.\n", old_value);
}

// Function to display the elements of the min priority queue
void display(MinPriorityQueue *pq)
{
    printf("Min Priority Queue: ");
    for (int i = 0; i < pq->size; i++)
    {
        printf("%d ", pq->heap[i]);
    }
    printf("\n");
}
