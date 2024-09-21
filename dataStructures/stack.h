#include<stdio.h>
#include<stdlib.h>
#define maxsize 50

struct stack{
    int a[maxsize];
    int top;
};

void init(struct stack *s){
    s->top=-1;
}

void push(struct stack *s, int data){
    if(s->top==maxsize-1){
        printf("stack is full");
        return;
    }
    s->a[++s->top]=data;
}

void pop(struct stack *s){
    if(s->top==-1){
        printf("stack is empty");
        return;
    }
    printf("popped element is %d",s->a[s->top--]);
}

int peek(struct stack *s){
    if(s->top==-1){
        printf("stack is empty");
        return -1;
    }
    return s->a[s->top];
}

void display(struct stack *s){
    if(s->top==-1){
        printf("stack is empty");
        return;
    }
    for(int i=s->top;i>=0;i--){
        printf("%d ",s->a[i]);
    }
}