#include<stdio.h>
#include<stdlib.h>
#define max 50

struct queue{
    int data[max];
    int size;
};

void init(struct queue *q){
    q->size=0;
}

void insert(struct queue *q, int val){
    if(q->size==max){
        printf("queue is full");
        return;
    }
    q->data[q->size]=val;
    q->size++;
    heapify_up(q,q->size-1);
}

void heapify_up(struct queue *q,int index){
    int parent=(index-1)/2;
    if(parent>=0 && q->data[parent]<q->data[index]){
        swap(q->data[parent],q->data[index]);
        heapify_up(q,parent);
    }
}

void swap(int a , int b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}

void delete(struct queue *q){
    if(q->size==0){
        printf("queue is empty");
        return;
    }
    int max=q->data[0];
    printf("max element is %d",max);
    q->data[0]=q->data[q->size-1];
    q->size--;
    heapify_down(q,0);
}

void heapify_down(struct queue *q, int index){
    int left=2*index+1;
    int right=2*index+2;
    int largest= index;
    if(left<q->size && q->data[largest]<q->data[left]){
        largest=left;
    }
    if(right<q->size && q->data[largest]<q->data[right]){
        largest=right;
    }
    if(largest!=index){
        swap(q->data[largest],q->data[index]);
        heapify_down(q,largest);
    }
}