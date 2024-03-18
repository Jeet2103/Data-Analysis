#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
    int size;
    int *arr;
    int capacity;
} heap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

heap *createheap(int capacity, int *nums);
void inserthelper(heap *h, int index);
void heappfy(heap *h, int index);
int extractmin(heap *h);
void insert(heap *h, int data);
void update(heap *h, int oldData, int newData);
void printheap(heap *h);

heap *createheap(int total, int *nums)
{
    heap *h = (heap *)malloc(sizeof(heap));
    if (h == NULL)
    {
        printf("Memory allocation failed.");
    }
    h->capacity = total;
    h->size = 0;
    h->arr = (int *)malloc(total * sizeof(int));
    if (h->arr == 0)
    {
        printf("Memory allocation failed");
        return NULL;
    }
    int i;
    for (i = 0; i < total; i++)
    {
        h->arr[i] = nums[i];
    }
    h->size = i;
    i = (h->size - 2) / 2;
    while (i >= 0)
    {
        heappfy(h, i);
        i--;
    }
    return h;
}

void insert(heap *h, int data)
{
    if (h->size < h->capacity)
    {
        int i = h->size;
        h->arr[h->size] = data;
        inserthelper(h, i);
        h->size++;
    }
}

void inserthelper(heap *h, int index)
{
    int parent = (index - 1) / 2;
    if (h->arr[parent] > h->arr[index])
    {
        swap(&h->arr[parent], &h->arr[index]);
        inserthelper(h, parent);
    }
}

int extractmin(heap *h)
{
    if (h->size == 0)
    {
        printf("\nHeap is empty.");
        return -999;
    }
    int deleted_item = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heappfy(h, 0);
    return deleted_item;
}

void heappfy(heap *h, int index)
{
    int left = (index * 2) + 1;
    int right = (index * 2) + 2;
    int min = index;
    if (left > h->size || left < 0)
    {
        left = -1;
    }
    if (right > h->size || right < 0)
    {
        right = -1;
    }

    if (left != -1 && h->arr[left] < h->arr[index])
    {
        min = left;
    }
    if (right != -1 && h->arr[right] < h->arr[min])
    {
        min = right;
    }
    if (min != index)
    {
        swap(&h->arr[min], &h->arr[index]);
        heappfy(h, min);
    }
}

void update(heap *h, int oldData, int newData)
{
    int i;
    for (i = 0; i < h->size; i++)
    {
        if (h->arr[i] == oldData)
        {
            h->arr[i] = newData;
            if (newData < oldData)
            {
                inserthelper(h, i);
            }
            else
            {
                heappfy(h, i);
            }
            return;
        }
    }
    printf("Element not found in the heap.\n");
}

void printheap(heap *h)
{
    int i;
    for (i = 0; i < h->size; i++)
    {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

int main()
{
    int choice, data, oldData, newData,total;
    printf("Enter the total number:\n");
    scanf("%d",&total);
    int *arr= (int*)malloc(total*sizeof(int));
    // int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    heap *hp = createheap(total, arr);

    do
    {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Update\n");
        printf("4. Display\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            insert(hp, data);
            break;
        case 2:
            extractmin(hp);
            break;
        case 3:
            printf("Enter the data to be updated: ");
            scanf("%d", &oldData);
            printf("Enter the new data: ");
            scanf("%d", &newData);
            update(hp, oldData, newData);
            break;
        case 4:
            printheap(hp);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
