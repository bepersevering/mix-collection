#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;


typedef struct Graph {
    int numVertices;
    Node **adjLists;
} Graph;

// rear 最后一个元素的下一个可用位置
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int *array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int *)malloc(queue->capacity * sizeof(int));

    return queue;
}

bool isFull(Queue *queue) {
    return (queue->size == queue->capacity);
}

bool isEmpty(Queue *queue) {
    return (queue->size == 0);
}

// 入队
void enqueue(Queue *queue, int item) {
    if (isFull(queue)) {
        return; 
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size += 1;
}

// 出队
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }

    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size -= 1;

    return item;
}


// create a node
Node* createNode(int v) {
    Node* node = (Node*)malloc(sizeof(Node));

    node->vertex = v;
    node->next = NULL;
    return node;
}

// create a graph with n vertices
Graph* createGraph(int n) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));

    graph->numVertices = n;
    graph->adjLists = (Node**)malloc(n*sizeof(Node*));
    for (int i = 0; i < n; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// add edge to undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // add edge from src to dest
    Node* srcNode = createNode(src);
    srcNode->next = graph->adjLists[src];
    graph->adjLists[src] = srcNode;

    
    Node* destNode = createNode(dest);
    destNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = destNode;
}









