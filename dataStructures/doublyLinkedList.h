#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

int isEmpty(struct node *head) {
    return head == NULL;
}

void insertBeg(struct node **head, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->prev = NULL;
    
    if (isEmpty(*head)) {
        *head = temp;
        temp->next = NULL;
    } else {
        temp->next = *head;
        (*head)->prev = temp;
        *head = temp;
    }
}

void insertEnd(struct node **head, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    
    if (isEmpty(*head)) {
        *head = temp;
        temp->prev = NULL;
    } else {
        struct node *a = *head;
        while (a->next != NULL) {
            a = a->next;
        }
        a->next = temp;
        temp->prev = a;
    }
}

void insertPos(struct node **head, int data, int pos) {
    if (pos == 0) {
        insertBeg(head, data);
        return;
    }
    
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    
    struct node *a = *head;
    for (int i = 0; i < pos - 1 && a != NULL; i++) {
        a = a->next;
    }
    
    if (a == NULL) {
        printf("Position out of range\n");
        free(temp);
        return;
    }
    
    temp->next = a->next;
    temp->prev = a;
    if (a->next != NULL) {
        a->next->prev = temp;
    }
    a->next = temp;
}

void deleteBeg(struct node **head) {
    if (isEmpty(*head)) {
        printf("List is empty\n");
        return;
    }
    
    struct node *temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

void deleteEnd(struct node **head) {
    if (isEmpty(*head)) {
        printf("List is empty\n");
        return;
    }
    
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    
    struct node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}

void deletePos(struct node **head, int pos) {
    if (isEmpty(*head)) {
        printf("List is empty\n");
        return;
    }
    
    if (pos == 0) {
        deleteBeg(head);
        return;
    }
    
    struct node *temp = *head;
    for (int i = 0; i < pos && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }
    
    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

void display(struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}



