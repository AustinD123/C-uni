#include <stdlib.h>
#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

struct queue
{
    struct node *front, *rear;
};

void initQueue(struct queue *pq);
void enqueue(struct queue *pq, int ele);
void dequeue(struct queue *pq);
int isEmpty(struct queue *pq);
void display(struct queue *pq);

void initQueue(struct queue *pq) {
    pq->front = pq->rear = NULL;
}

int isEmpty(struct queue *pq) {
    return pq->front == NULL;
}

void enqueue(struct queue *pq, int ele) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    temp->data = ele;
    temp->next = NULL;
    if (isEmpty(pq)) {
        pq->front = pq->rear = temp;
    } else {
        pq->rear->next = temp;
        pq->rear = temp;
    }
}

void dequeue(struct queue *pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty\n");
        return;
    }
    struct node *temp = pq->front;
    printf("The deleted element is %d\n", temp->data);
    pq->front = pq->front->next;
    free(temp);
    if (pq->front == NULL) {
        pq->rear = NULL;
    }
}

void display(struct queue *pq) {
    struct node *p = pq->front;
    if (p == NULL) {
        printf("Empty Queue\n");
        return;
    }
    
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}