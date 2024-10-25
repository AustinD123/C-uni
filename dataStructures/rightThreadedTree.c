#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>

struct node{
    int data;
    struct node * left;
    struct node * right;
    bool rthread;
}

struct tree{
    struct node * root;
}

void init(struct tree *pt){
    pt->root==NULL;
}

struct node* createNode(int data){
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->data=data;
    temp->left=temp->right=NULL;
    temp->rthread=1;
    return temp;
}

void setLeft(struct node *p,int e){
    struct node *temp=createNode(e);
    p->left=temp;
    temp->right=p;
}

void setRight(struct node *p,int e){
    struct node *temp=createNode(e);
    temp->right=p->right;
    p->right=temp;
    p->rthread=0;
}

void inorder(struct tree *t){
    struct node *p=t->root;
    struct node *q;
    do{
        q=NULL;
        while(p!=NULL){
            q=p;
            p=p->left;
        }
        if(q!=NULL){
            printf("%d",q->data);
            p=q->right;
        }
        while(q->thread && p!=NULL){
            printf("%d",p->info);
            q=p;
            p=p->right;
        }
    }while(q!=NULL);

}
void create(TREE *pt)
{
    NODE *p,*q;
    int e,wish;
    printf("Enter root info\n");
    scanf("%d",&e);
    pt->root=createNode(e);
    do{
        printf("Enter info\n");
        scanf("%d",&e);
        p=pt->root;
        q=NULL;
        while(p!=NULL)
        {
            q=p;
            if(e<p->info)
               p=p->left;
            else{
                if(p->rthread)
                    p=NULL;
            else
                p=p->right;
            }
        }
        if(e < q->info)
            setLeft(q,e);
        else
            setRight(q,e);
        printf("Do you wish to add another element\n");
        scanf("%d",&wish);
    }while(wish);
}

int main()
    {
    TREE t;
    init(&t);
    create(&t);
    inOrder(&t);
    return 0;
}