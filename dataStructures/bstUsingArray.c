#include<stdio.h>

struct node{
    int data; 
    int used
}

#define max 50

void init(struct node tree[50]){
    for(int i=0;i<max;i++){
        tree[i].used=0;
    }
}

void createBST(struct node *t){
    int ele,wish;
    printf("Enter the root element\n");
    scanf("%d",&bst[0].info);
    bst[0].used=1;
    do{
        printf("Enter an element\n");
        scanf("%d",&ele);
        int p=0;
        while(p<max && t[p].used){
            if(ele<bst[p].data)
                p=2*p+1;
            else
                p=2*p+2;
        }
        if(p>=max){
            printf("insertion not possible");
        }
        else{
            t[p]->info=ele;
            t[p]->used=1;
        }
        printf("do you wish to add another node");
        scanf("%d",&wish);
    }while(wish);
}

void inorder(struct node *t,int r){
    if(t[r].used){
        inorder(t,2*r+1);
        printf("%d",t[r]->data);
        inorder(t,2*r+2);
    }
}

