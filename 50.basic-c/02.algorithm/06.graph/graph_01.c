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
    
}





