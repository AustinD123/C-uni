#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertAtBeginning(struct Node** head, int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = *head;
    *head = temp;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    if (*head == NULL) {
        *head = temp;
        return;
    }
    struct Node* a = *head;
    while (a->next != NULL) {
        a = a->next;
    }
    a->next = temp;
}

void insertAtPosition(struct Node** head, int data, int position) {
    if (position == 0) {
        insertAtBeginning(head, data);
        return;
    }
    
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    
    struct Node* a = *head;
    for (int i = 0; i < position - 1 && a != NULL; i++) {
        a = a->next;
    }
    
    if (a == NULL) {
        printf("Position out of bounds\n");
        free(temp); // Avoid memory leak
        return;
    }
    
    temp->next = a->next;
    a->next = temp;
}

void deleteFirstNode(struct Node** head) {
    if (*head == NULL) return;
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteLastNode(struct Node** head) {
    if (*head == NULL) return;
    
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    
    struct Node* a = *head;
    while (a->next->next != NULL) {
        a = a->next;
    }
    
    free(a->next);
    a->next = NULL;
}

void displayList(struct Node* head) {
    struct Node* a = head;
    while (a != NULL) {
        printf("%d -> ", a->data);
        a = a->next;
    }
    printf("NULL\n");
}

int isEmpty(struct Node* head) {
    return head == NULL;
}
