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

// BFS traversal from a given source vertex
int* bfs(Graph* graph, int start, int* visitOrder, int* visitCount) {
    // Mark all vertices as not visited
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));

    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    // create a queue for bfs
    Queue *queue = createQueue(graph->numVertices);

    // Mark the current node as visited and enqueue it
    visited[start] = true;
    enqueue(queue, start);

    *visitCount = 0;

    // BFS loop
    while (!isEmpty(queue)) {
        // dequeue a vertex and add to visit order
        int currentVertex = dequeue(queue);
        visitOrder[(*visitCount)++] = currentVertex;

        // get all adjacent vertices of the dequeue vertex
        // If an adjacent hasn't been visited, mark it visited and enqueue it
        Node *temp = graph->adjLists[currentVertex];

        while(temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    
    }

    free(visited);
    free(queue->array);
    free(queue);

    return visitOrder;
}



void test() {
    int numVertices = 5;

    Graph* graph = createGraph(numVertices);

    // add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    int* visitOrder = (int*)malloc(numVertices*sizeof(int));
    
    int visitCount = 0;

    visitOrder = bfs(graph, 0, visitOrder, &visitCount);
    
    printf("BFS traversal starting from vertex 0: ");
    
    for (int i = 0; i < visitCount; i++) {
        printf("%d ", visitOrder[i]);
    }

    printf("\n");
    
    free(visitOrder);

}


int main() {
    test();
    return 0;
}



