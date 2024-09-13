#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct message {
    char sender[50];
    char content[50];
    struct message *next;
    int highlighted;
};

void insert_message(struct message **list_start, char sender[], char content[]) {
    struct message *new_msg = (struct message *)malloc(sizeof(struct message));
    if (new_msg == NULL) {
        printf("Error: Unable to allocate memory\n");
        return;
    }
    strncpy(new_msg->sender, sender, sizeof(new_msg->sender) - 1);
    strncpy(new_msg->content, content, sizeof(new_msg->content) - 1);
    new_msg->highlighted = 0;
    new_msg->next = NULL;
    if (*list_start == NULL) {
        *list_start = new_msg;
    } else {
        struct message *current = *list_start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_msg;
    }
}

void show_messages(struct message *list_start) {
    if (list_start == NULL) {
        printf("Chat history is empty\n");
        return;
    }
    struct message *current = list_start;
    while (current != NULL) {
        if (current->highlighted == 0) {
            printf("From: %s\n", current->sender);
            printf("Message: %s\n\n", current->content);
        }
        current = current->next;
    }
}

void highlight_message(struct message **regular_list, struct message **highlighted_list) {
    char target_sender[50];
    printf("Enter sender name to highlight: ");
    scanf("%s", target_sender);
    struct message *current = *regular_list;
    while (current != NULL) {
        if (strcmp(current->sender, target_sender) == 0) {
            current->highlighted = 1;
            insert_message(highlighted_list, current->sender, current->content);
            printf("Message successfully highlighted.\n");
            return;
        }
        current = current->next;
    }
    printf("Error: No message found from the specified sender\n");
}

void remove_highlight(struct message **regular_list, struct message **highlighted_list) {
    char target_sender[50];
    printf("Enter sender name to remove highlight: ");
    scanf("%s", target_sender);
    struct message *current = *highlighted_list;
    struct message *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->sender, target_sender) == 0) {
            if (prev == NULL) {
                *highlighted_list = current->next;
            } else {
                prev->next = current->next;
            }
            struct message *regular_msg = *regular_list;
            while (regular_msg != NULL) {
                if (strcmp(regular_msg->sender, target_sender) == 0) {
                    regular_msg->highlighted = 0;
                    break;
                }
                regular_msg = regular_msg->next;
            }
            free(current);
            printf("Highlight removed successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Error: No highlighted message found from the specified sender\n");
}

void display_all_messages(struct message *regular_list, struct message *highlighted_list) {
    printf("=== HIGHLIGHTED MESSAGES ===\n");
    show_messages(highlighted_list);
    printf("=== REGULAR MESSAGES ===\n");
    show_messages(regular_list);
}

int main() {
    struct message *regular_list = NULL;
    struct message *highlighted_list = NULL;
    int user_choice;
    char sender[50], content[50];
    while (1) {
        printf("\n1. Add new message\n2. View chat history\n3. Highlight a message\n4. Remove highlight\n5. View all messages\n6. Exit\n");
        printf("Select an option: ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1:
                printf("Enter sender name: ");
                scanf("%s", sender);
                printf("Enter message content: ");
                scanf(" %[^\n]", content);
                insert_message(&regular_list, sender, content);
                break;
            case 2:
                show_messages(regular_list);
                break;
            case 3:
                highlight_message(&regular_list, &highlighted_list);
                break;
            case 4:
                remove_highlight(&regular_list, &highlighted_list);
                break;
            case 5:
                display_all_messages(regular_list, highlighted_list);
                break;
            case 6:
                while (regular_list != NULL) {
                    struct message *temp = regular_list;
                    regular_list = regular_list->next;
                    free(temp);
                }
                while (highlighted_list != NULL) {
                    struct message *temp = highlighted_list;
                    highlighted_list = highlighted_list->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Error: Invalid option. Please try again.\n");
        }
    }
    return 0;
}