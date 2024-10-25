#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define max 50

struct node{
    char info;
    struct node *left;
    struct node *right;
}NODE;

struct tree{
    NODE *root;
}TREE;

struct stack{
    int top;
    NODE *s[max];
}STACK;

void initTree(TREE *pt){
    pt->root=NULL;
}

void initStack(STACK *ps){
    ps->top=-1;
}

void push(STACK *ps, NODE *e){
    if(ps->top=max-1){
        return;
    }
    ps->top++;
    ps->s[ps->top]=e;
}

NODE* pop(STACK *ps) {
    NODE *t = ps->s[ps->top];
    ps->top--;
    return t;
}

float eval(NODE *r){
    float res;
    switch(r->info){
        case '+':return eval(r->left) + eval(r->right);
        case '-':return eval(r->left) - eval(r->right);
        case '*':return eval(r->left)*eval(r->right);
        case '/':return eval(r->left)/eval(r->right);
        default: return r->info-'0';
    }
    return res;
}

float eval1(TREE *pt){
    return eval(pt->root);
}

int main(){
    char postfix[max];
    STACK sobj;
    TREE tobj;
    NODE *temp;
    
    init_stack(&sobj);
    
    printf("Enter a valid postfix expression\n");
    scanf("%s", postfix);
    
    int i = 0;
    while(postfix[i]!='\0'){
        NODE *temp=(NODE *)malloc(sizeof(NODE));
        temp->info=postfix[i];
        temp->right=temp->left=NULL;
        if(isdigit(postfix[i])){
            push(&sobj,temp);
        }
        else{
            temp->right=pop(&sobj);
            temp->left=pop(&sobj);
            push(&sobj,temp);
        }
        i++;
    }
    tobj.root = pop(&sobj);
    printf("%f", eval_tree(&tobj));
    
    return 0;
}