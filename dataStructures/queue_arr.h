#include <stdio.h>
#include <stdlib.h>
#define max 50

struct queue {
    int a[max];
    int front;
    int rear;
};  

void enqueue(struct queue *pq, int ele);
void initQueue(struct queue *pq);
int dequeue(struct queue *pq);
int isFull(struct queue *pq);
int isEmpty(struct queue *pq);
void display(struct queue *pq);

void initQueue(struct queue *pq) {
    pq->rear = pq->front = -1;
}

int isEmpty(struct queue *pq) {
    return pq->rear == pq->front;
}

int isFull(struct queue *pq) {
    return pq->rear == max - 1; 
}

void enqueue(struct queue *pq, int ele) { 
    if (isFull(pq)) {
        printf("Queue is full\n");
        return;
    }
    pq->a[++(pq->rear)] = ele;
}

int dequeue(struct queue *pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty\n");
        return -1; 
    }
    int x = pq->a[++(pq->front)];
    if (pq->front == pq->rear) {
        pq->rear = pq->front = -1;
    }
    return x;
}

void display(struct queue *pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty\n");
        return;
    }
    for (int i = pq->front + 1; i <= pq->rear; i++) {  
        printf("%d ", pq->a[i]);
    }
    printf("\n");
}