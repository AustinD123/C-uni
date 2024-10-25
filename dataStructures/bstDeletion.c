#include<stdio.h>
#include<stdlib.h>

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

void createTree(struct tree *pt){
    struct node *p,*q;
    int e, wish;
    printf("enter node info\n");
    scanf("%d",&e);
    pt->root=createNode(e);
    do{
        printf("enter info\n");
        scanf("%d",&e);
        q=NULL;
        p=pt->root;
        while(p!=NULL){
            q=p;
            if(e>p->data){
                p=p->right;
            }
            else
                p=p->left;
        }
        if(e<q->infor){
            q->left=createNode(e);
        }
        else{
            q->right=createNode(e);
        }
        printf("Do you wish to continue\n");
        scanf("%d",&wish);

    }while(wish);
}

void io(struct node *r){
    if(r!=NULL){
        io(r->left);
        printf("%d",r->info);
        io(r->right);    }
}

void inorder(struct tree *pt){
    io(pt->root);
}

struct node* deleteNode(struct node *r, int ele){
    struct node *temp,*p;
    if(r==NULL){
        return r;
    }
    if(ele<r->info){
        r->left=deleteNode(r->left,ele);
    }
    else if(ele>r->info){
        r->right=deleteNode(r->right,ele);
    }
    else{
        if(r->left==NULL){
            temp=r->right;
            free(r);
            return temp;
        }
        else if(r->right==NULL){
            temp=r->left;
            free(r);
            return temp;
        }
        else{
            p=r->right;
            while(p->left!=NULL){
                p=p->left;
            }
            r->info=p->info;
            r->right=deleteNode(r->right,p->info);
        }
    }
    return r;
}

void deleteNode(struct tree *pt, int e){
    pt->root=deleteNode(pt->root,e);
}
