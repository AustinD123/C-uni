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
c:\Users\austi\DSA-Programs
void initQueue(struct queue *pq) {
    pq->rear = pq->front = -1;
}

int isEmpty(struct queue *pq) {
    return pq->rear ==-1 && pq->front ==-1;
}

int isFull(struct queue *pq) {
    return ((pq->rear +1)/max==pq->front) ; 
}

void enqueue(struct queue *pq, int ele) { 
    if (isFull(pq)) {
        printf("Queue is full\n");
        return;
    }
    if(pq->rear==max-1 && pq->front!=0){
        pq->rear=-1;
    }
    pq->a[++(pq->rear)] = ele;
    if(pq->front == -1){
        pq->front++;
    }
}

int dequeue(struct queue *pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty\n");
        return -1; 
    }
    int x = pq->a[++(pq->front)];
    if(pq->front==max){
        pq->front = 0;
    }
    if (pq->front-1 == pq->rear) {
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