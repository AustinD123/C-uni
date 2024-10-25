#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *left,*right;
};
struct tree{
    struct node *tree;
};

void initTree(struct tree *pt);
void createsTree(struct tree *pt);
void inorder(struct tree *pt);
void preorder(struct tree *pt);
void postorder(struct tree *pt);
void destroyTree(struct tree *pt);

void initTree(struct tree *pt){
    pt->NULL;
}
void createsTree(struct tree *pt){
    int choice;
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->left=NULL;
    temp->right=NULL;
    pt->root = temp;

	printf("Do you want to add one more node\n");
	scanf("%d", &choice);
    printf("Enter node info\n");
	scanf("%d", &temp->info);
	while (choice){
        temp=(struct node *)malloc(sizeof(struct node));
        temp->right=temp->left=NULL;
        struct node *p,*q;
        p=root;
        q=NULL;
        while(p!=NULL){
            if(p->info<temp->info){
                q=p;
                p=p->right;
            }
            else{
                q=p;
                p=p->left;
            }
        }
        if (temp->info <= q->info)
			q->left = temp;
		else
			q->right = temp;
		printf("Do you want to add one more node\n");
		scanf("%d", &choice);
    }
}

void inord(struct node *r)
{
	if (r == NULL)
		return;
	inord(r->left);
	printf("%d ", r->info);
	inord(r->right);
}
void inorder(struct tree *pt)
{
	inord(pt->root);
}
void preord(struct node *r)
{
	if (r != NULL)
	{
		printf("%d ", r->info);
		preord(r->left);
		preord(r->right);
	}
}
void preorder(struct tree *pt)
{
	preord(pt->root);
}
void postord(struct node *r)
{
	if (r != NULL)
	{
		postord(r->left);
		postord(r->right);
		printf("%d ", r->info);
	}
}
void postorder(struct tree *pt)
{
	postord(pt->root);
}
