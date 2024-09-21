#include<stdio.h>
#include<stdlib.h>


struct stack{
    int data;
    struct stack *next;
};

void init(struct stack *top){
    top=NULL;
}

void push(struct stack **top, int data){
    struct stack *temp=(struct stack *)malloc(sizeof(struct stack));
    temp->data=data;
    if(*top==NULL){
        temp->next=NULL;
        *top=temp;
        return;
    }
    temp->next=*top;
    *top=temp;
}

void pop(struct stack **top){
    if(*top==NULL){
        printf("stack is empty");
        return;
    }
    struct stack *temp=(struct stack *)malloc(sizeof(struct stack));
    temp=*top;
    printf("popped element is %d",temp->data);
    *top=temp->next;
    free(temp);
}

int peek(struct stack *top){
    if(*top==NULL){
        printf("stack is empty");
        return -1;
    }
    return top->data;
}

void display(struct stack *top){
    if(top==NULL){
        printf("stack is empty");
        return -1;
    }
    struct stack *temp=(struct stack *)malloc(sizeof(struct stack));
    temp=top;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }
}