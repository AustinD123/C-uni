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
    
    if (isEmpty(*head)) {
        *head = temp;
        temp->next = temp;
        temp->prev = temp;
    } else {
        temp->next = *head;
        temp->prev = (*head)->prev;
        (*head)->prev->next = temp;
        (*head)->prev = temp;
        *head = temp;
    }
}

void insertEnd(struct node **head, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    
    if (isEmpty(*head)) {
        *head = temp;
        temp->next = temp;
        temp->prev = temp;
    } else {
        temp->next = *head;
        temp->prev = (*head)->prev;
        (*head)->prev->next = temp;
        (*head)->prev = temp;
    }
}

void insertPos(struct node **head, int data, int pos) {
    if (pos == 0) {
        insertBeg(head, data);
        return;
    }
    
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    
    struct node *current = *head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
        if (current == *head) {
            printf("Position out of range\n");
            free(temp);
            return;
        }
    }
    
    temp->next = current->next;
    temp->prev = current;
    current->next->prev = temp;
    current->next = temp;
}

void deleteBeg(struct node **head) {
    if (isEmpty(*head)) {
        printf("List is empty\n");
        return;
    }
    
    struct node *temp = *head;
    
    if ((*head)->next == *head) {
        *head = NULL;
    } else {
        (*head)->prev->next = (*head)->next;
        (*head)->next->prev = (*head)->prev;
        *head = (*head)->next;
    }
    
    free(temp);
}

void deleteEnd(struct node **head) {
    if (isEmpty(*head)) {
        printf("List is empty\n");
        return;
    }
    
    struct node *temp = (*head)->prev;
    
    if ((*head)->next == *head) {
        *head = NULL;
    } else {
        temp->prev->next = *head;
        (*head)->prev = temp->prev;
    }
    
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
    for (int i = 0; i < pos; i++) {
        temp = temp->next;
        if (temp == *head) {
            printf("Position out of range\n");
            return;
        }
    }
    
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    
    free(temp);
}

void display(struct node *head) {
    if (isEmpty(head)) {
        printf("List is empty\n");
        return;
    }
    
    struct node *temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}
