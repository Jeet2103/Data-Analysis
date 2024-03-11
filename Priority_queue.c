#include<stdio.h>
#include<stdlib.h>
typedef struct heap
{
   int size;
   int *arr;
   int capacity;
} heap;
void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
heap* createheap(int capacity, int* nums);
void inserthelper(heap* h, int index);
void heappfy(heap* h, int index);
int extractmin(heap* h);
void insert(heap* h, int data);

heap * createheap(int total , int *nums){
    heap * h=(heap*)malloc(sizeof (heap));
    if (h==NULL)
    {
        printf("Memory allocation failed.");
    }
    h->capacity=total;
    h->size=0;
    h->arr=(int*)malloc(total * sizeof(int));
    if (h->arr==0)
    {
        printf("memory allocation failed");
        return NULL;

    }
    int i;
    for(i=0;i<total;i++){
        h->arr[i]=nums[i];
    }
    h->size=i;
    i=(h->size-2)/2;
    while (i>=0)
    {
       heappfy(h,i);
       i--;
    }
    return h;
    
}
void insert(heap *h , int data){
    if (h->size<h->capacity)
    {
        int i=h->size;
       h->arr[h->size]=data;
       inserthelper(h,i);
       h->size++;

    }
   
}
void inserthelper(heap*h,int index){
    int parent=(index-1)/2;
    if (h->arr[parent]>h->arr[index])
    {
        swap(& h->arr[parent], & h->arr[index]);
        inserthelper(h,parent);
    }
    
}
int extractmin(heap *h ){
    if (h->size == 0) {
		printf("\nHeap id empty.");
		return -999;
	}
    int deleted_item=h->arr[0];
    h->arr[0]=h->arr[h->size-1];
    h->size--;
    heappfy(h,0);
    return deleted_item;

}
void heappfy(heap * h, int index){
    int left=(index*2) +1;
    int rigth = (index*2) +2;
    int min =index;
    if (left>h->size || left<0)
    {
        left=-1;
    }
    if (rigth>h->size || rigth<0)
    {
        rigth=-1;
    }
    //main programme to heappify
    if (left!=-1 && h->arr[left]<h->arr[index])
    {
       min=left;
    }
    if (rigth!=-1 && h->arr[rigth]<h->arr[min])
    {
       min=rigth;
    }
    if (min != index) { //part to be remember
        swap(&h->arr[min], &h->arr[index]);
        heappfy(h, min);
    }
    
}
void printheap(heap *h){
    int i;
    for ( i = 0; i < h->size; i++)
    {
        printf("%d ",h->arr[i]);
    }
    printf("\n");
}
int main()
{
    int arr[9] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    heap* hp = createheap(9, arr);
 
    printheap(hp);
    extractmin(hp);
    printheap(hp);
 
    return 0;
}