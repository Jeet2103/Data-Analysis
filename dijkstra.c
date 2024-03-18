#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Node {
    int id;
    Edge* edges;
} Node;

typedef struct Graph {
    int numNodes;
    Node* nodes;
} Graph;

typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int* pos;
    HeapNode** array;
} MinHeap;

Graph* createGraph(int numNodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;
    graph->nodes = (Node*)malloc(numNodes * sizeof(Node));
    for (int i = 0; i < numNodes; ++i) {
        graph->nodes[i].id = i;
        graph->nodes[i].edges = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->dest = dest;
    edge->weight = weight;
    edge->next = graph->nodes[src].edges;
    graph->nodes[src].edges = edge;
}

HeapNode* createHeapNode(int vertex, int distance) {
    HeapNode* newNode = (HeapNode*)malloc(sizeof(HeapNode));
    newNode->vertex = vertex;
    newNode->distance = distance;
    return newNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HeapNode**)malloc(capacity * sizeof(HeapNode*));
    return minHeap;
}

void swapHeapNodes(HeapNode** a, HeapNode** b) {
    HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->distance < minHeap->array[smallest]->distance)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->distance < minHeap->array[smallest]->distance)
        smallest = right;
    if (smallest != idx) {
        HeapNode* smallestNode = minHeap->array[smallest];
        HeapNode* idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;
        swapHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

HeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;
    HeapNode* root = minHeap->array[0];
    HeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}

void decreaseDistance(MinHeap* minHeap, int vertex, int distance) {
    int i = minHeap->pos[vertex];
    minHeap->array[i]->distance = distance;
    while (i && minHeap->array[i]->distance < minHeap->array[(i - 1) / 2]->distance) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void printSolution(int dist[], int n, int parent[]) {
    printf("Vertex   Distance from Source   Path\n");
    for (int i = 0; i < n; ++i) {
        printf("%d \t\t %d \t\t\t", i, dist[i]);
        int j = i;
        while (parent[j] != -1) {
            printf("%d <- ", j);
            j = parent[j];
        }
        printf("%d\n", j);
    }
}

void dijkstra(Graph* graph, int src) {
    int V = graph->numNodes;
    int dist[V];
    int parent[V]; // To store the parent node for each vertex in the shortest path
    MinHeap* minHeap = createMinHeap(V);
    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        parent[v] = -1; // Initialize parent array with -1
        minHeap->array[v] = createHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    minHeap->array[src] = createHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseDistance(minHeap, src, dist[src]);
    minHeap->size = V;
    while (!isEmpty(minHeap)) {
        HeapNode* heapNode = extractMin(minHeap);
        int u = heapNode->vertex;
        Edge* pCrawl = graph->nodes[u].edges;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            if (dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
                parent[v] = u; // Update parent for vertex v
                decreaseDistance(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    printSolution(dist, V, parent);
}

int main() {
    FILE* fp = fopen("graph_input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int numNodes;
    fscanf(fp, "%d", &numNodes);

    Graph* graph = createGraph(numNodes);
    int src, dest, weight;
    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF) {
        addEdge(graph, src, dest, weight);
    }

    fclose(fp);

    dijkstra(graph, 0);
    return 0;
}
