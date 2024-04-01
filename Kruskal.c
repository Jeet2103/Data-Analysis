#include <stdio.h>
#include <stdlib.h>
typedef struct Edge {
    int src, dest, weight;
}Edge;
typedef struct Graph {
    int V, E;
    Edge* edge;
}Graph;
typedef struct subset {
    int parent,rank;
}subset;
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}
int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
void swap(Edge*a,Edge*b)
{
    Edge temp=*a;
    *a=*b;
    *b=temp;
}
int partition(Edge* arr,int l,int r)
{
    int pivot;
    int i=l-1,j;
    pivot=arr[r].weight;
    for(j=l;j<r;j++)
    {
        if(arr[j].weight<pivot)
        {
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[r]);
    return i+1;
}
void quicksort(Edge* arr,int l,int r){
    if(l<r)
    {
        int pi=partition(arr,l,r);
        quicksort(arr,l,pi-1);
        quicksort(arr,pi+1,r);
    }
}
void KruskalMST(Graph* graph) {
    int V = graph->V,v,x,y,i,sum=0;
    Edge result[V],next_edge; 
    int e = 0; 
    subset* subsets = (subset*)malloc(V * sizeof(subset));
    quicksort(graph->edge,0,graph->E-1);
    for (v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    while (e < V - 1 && graph->E != 0) {
        next_edge = graph->edge[0];
        graph->edge++;
        x = find(subsets, next_edge.src);
        y = find(subsets, next_edge.dest);
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    printf("Edges in MST:\n");
    for (i = 0; i < e; ++i)
    {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        sum+=result[i].weight;
    }
    printf("Total weight of MST:%d",sum);
    free(subsets);
}
void print(Graph* graph)
{
    int v;
    printf("Graph\n");
    for(v=0;v<graph->E;v++)
    printf("%d--%d\n",graph->edge[v].src,graph->edge[v].dest);
}
int main() {
    FILE*fp;
    Graph*graph;
    int V,v1,v2,wt,i=0,val,E=0;
    fp=fopen("graph_input.txt","r");
    fscanf(fp,"%d",&V);
    while(fscanf(fp,"%d%d%d",&v1,&v2,&wt)!=EOF)
    E++;
    rewind(fp);
    graph = createGraph(V,E);
    fscanf(fp,"%d",&val);
    while(fscanf(fp,"%d%d%d",&v1,&v2,&wt)!=EOF)
    {
        graph->edge[i].src=v1;
        graph->edge[i].dest=v2;
        graph->edge[i++].weight=wt;
    }
    print(graph);
    KruskalMST(graph);
    fclose(fp);
    free(graph->edge);
    free(graph);
    return 0;
}