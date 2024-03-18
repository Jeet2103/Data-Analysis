#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
}AdjListNode;
typedef struct AdjList
{
   AdjListNode *head; 
}AdjList;
typedef struct Graph
{
    int V;
    AdjList* array;
}Graph;
typedef struct MinHeapNode
{
    int  v;
    int dist;
}MinHeapNode;
typedef struct MinHeap
{
    int size;     
    int capacity;  
    int *pos;    
    MinHeapNode **array;
}MinHeap;
AdjListNode* newAdjListNode(int dest, int weight)
{
    AdjListNode* newNode =(AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
Graph* createGraph(int V)
{
    int i;
    Graph* graph=(Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array=(AdjList*)malloc(V*sizeof(AdjList));
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}
void addEdge(Graph* graph, int src,int dest, int weight)
{
    AdjListNode*newNode=newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}
MinHeapNode* newMinHeapNode(int v,int dist)
{
    MinHeapNode* minHeapNode =(MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
MinHeap* createMinHeap(int capacity)
{
    MinHeap* minHeap =(MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =(MinHeapNode ** )malloc(capacity*sizeof(MinHeapNode*));
    return minHeap;
}
void swapMinHeapNode(MinHeapNode** a,MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(MinHeap* minHeap,int idx)
{
    MinHeapNode*smallestNode,*idxNode;
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    if (left<minHeap->size && minHeap->array[left]->dist<minHeap->array[smallest]->dist)
      smallest = left;
    if (right < minHeap->size && minHeap->array[right]->dist<minHeap->array[smallest]->dist)
      smallest = right;
    if (smallest != idx)
    {
        smallestNode=minHeap->array[smallest];
        idxNode=minHeap->array[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&minHeap->array[smallest],&minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
int isEmpty(MinHeap* minHeap)
{
    return minHeap->size == 0;
}
MinHeapNode* extractMin(MinHeap*minHeap)
{
    MinHeapNode*root,*lastNode;
    if (isEmpty(minHeap))
        return NULL;
    root=minHeap->array[0];
    lastNode =minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}
void decreaseKey(MinHeap* minHeap,int v, int dist)
{
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    while (i && minHeap->array[i]->dist<minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v]=(i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],&minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int isInMinHeap(MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return 1;
   return 0;
}
void printArr(int dist[], int n)
{
    int i;
    printf("Vertex   Distance from Source\n");
    for (i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
void dijkstra(Graph* graph, int src,int*parent)
{
    int V = graph->V,v,u;
    int *dist;     
    MinHeap* minHeap = createMinHeap(V);
    MinHeapNode*minHeapNode;
    AdjListNode*pCrawl;
    dist=(int*)malloc(V*sizeof(int));
    for(v = 0;v < V;v++)
    {
        dist[v]=INT_MAX;
        minHeap->array[v]=newMinHeapNode(v,dist[v]);
        minHeap->pos[v] = v;
    }
    minHeap->array[src]=newMinHeapNode(src, dist[src]);
    minHeap->pos[src]=src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;
    while (!isEmpty(minHeap))
    {
        minHeapNode=extractMin(minHeap);
        u = minHeapNode->v; 
        pCrawl=graph->array[u].head;
        while (pCrawl != NULL)
        {
            v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
                parent[v]=u;
            }
            pCrawl = pCrawl->next;
        }
    }
    printArr(dist, V);
    free(dist);
}
void print(Graph*graph)
{
    int i;
    AdjListNode*ptr;
    for(i=0;i<graph->V;i++)
    {
        ptr=graph->array[i].head;
        printf("%d->",i);
        while(ptr)
        {
            printf("%d->",ptr->dest);
            ptr=ptr->next;
        }
        printf("NULL\n");
    }
}
int main()
{
    FILE*fp;
    Graph*graph;
    int V,v1,v2,wt,i,val;
    int*parent,*arr,top,src=0;
    fp=fopen("graph_input.txt","r");
    fscanf(fp,"%d",&V);
    graph = createGraph(V);
    parent=(int*)malloc(V*sizeof(int));
    arr=(int*)malloc(V*sizeof(int));
    while(fscanf(fp,"%d%d%d",&v1,&v2,&wt)!=EOF)
    addEdge(graph,v1,v2,wt);
    printf("Graph\n");
    print(graph);
    for(i=0;i<V;i++)
    parent[i]=-1;
    dijkstra(graph,src,parent);
    printf("Paths\n");
    for(i=0;i<V;i++)
    {
        top=0;
        arr[top++]=i;
        val=parent[i];
        while(val!=-1)
        {
            arr[top++]=val;
            val=parent[val];
        }
        top--;
        while(top>-1){
        if(top>0)
        printf("%d->",arr[top--]);
        else
        printf("%d",arr[top--]);
        }
        printf("\n");
    }
    return 0;
}