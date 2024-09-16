#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};


void insertAtBeginning(struct Node** head, int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;

    if (*head == NULL) {
        temp->next = temp;
        *head = temp;
    } else {
        struct Node* a = *head;
        while (a->next != *head) {
            a = a->next;
        }
        temp->next = *head;
        a->next = temp;
        *head = temp;
    }
}


void insertAtEnd(struct Node** head, int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    
    if (*head == NULL) {
        temp->next = temp;
        *head = temp;
        return;
    }
    
    struct Node* a = *head;
    while (a->next != *head) {
        a = a->next;
    }
    a->next = temp;
    temp->next = *head; 
}


void insertAtPosition(struct Node** head, int data, int position) {
    if (position == 0) {
        insertAtBeginning(head, data);
        return;
    }
    
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    
    struct Node* a = *head;
    for (int i = 0; i < position - 1 && a->next != *head; i++) {
        a = a->next;
    }
    
    if (a->next == *head && position != 0) {
        printf("Position out of bounds\n");
        free(temp); 
        return;
    }
    
    temp->next = a->next;
    a->next = temp;
}


void deleteFirstNode(struct Node** head) {
    if (*head == NULL) return;
    
    struct Node* a = *head;
    struct Node* temp = *head;
    
    if ((*head)->next == *head) { 
        free(*head);
        *head = NULL;
        return;
    }
    
    while (a->next != *head) { 
        a = a->next;
    }
    
    *head = (*head)->next;
    a->next = *head; 
    free(temp);
}

void deleteLastNode(struct Node** head) {
    if (*head == NULL) return;

    struct Node* a = *head;
    struct Node* prev = NULL;

    if ((*head)->next == *head) { 
        free(*head);
        *head = NULL;
        return;
    }

    while (a->next != *head) {
        prev = a;
        a = a->next;
    }

    prev->next = *head; 
    free(a);
}

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node* a = head;
    do {
        printf("%d -> ", a->data);
        a = a->next;
    } while (a != head);
    printf("HEAD\n");
}

int isEmpty(struct Node* head) {
    return head == NULL;
}

