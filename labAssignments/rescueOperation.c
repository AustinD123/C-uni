#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rescue_operation.h"

struct Zone* first_zone = NULL;
struct Team* first_team = NULL;
struct Record* record_tree_root = NULL;

/* done by Aviyakth Rai*/
void add_zone(struct Zone* new_zone) {
    if (!new_zone) return;
    
    if (!first_zone || first_zone->priority_level > new_zone->priority_level) {
        new_zone->next_zone = first_zone;
        first_zone = new_zone;
        return;
    }
    
    struct Zone* current_zone = first_zone;
    while (current_zone->next_zone && current_zone->next_zone->priority_level <= new_zone->priority_level) {
        current_zone = current_zone->next_zone;
    }
    new_zone->next_zone = current_zone->next_zone;
    current_zone->next_zone = new_zone;
}

struct Zone* dequeue_highest_priority_zone() {
    if (!first_zone) return NULL;

    struct Zone* top_priority_zone = first_zone;
    first_zone = first_zone->next_zone;
    top_priority_zone->next_zone = NULL;
    return top_priority_zone;
}

/* done by Austin francis*/
void add_team(struct Team* new_team) {
    if (!new_team) return;
    
    new_team->next_team = first_team;
    first_team = new_team;
}

struct Team* find_team_with_supplies(struct Supplies* required_supplies) {
    struct Team* current_team = first_team;
    while (current_team) {
        if (current_team->available_supplies.food >= required_supplies->food &&
            current_team->available_supplies.first_aid_kits >= required_supplies->first_aid_kits &&
            current_team->available_supplies.water >= required_supplies->water &&
            current_team->available_supplies.clothing >= required_supplies->clothing) {
            return current_team;
        }
        current_team = current_team->next_team;
    }
    return NULL;
}

struct Record* create_record_node(int zone_id, int team_id, struct Supplies supplies_used) {
    struct Record* node = (struct Record*)malloc(sizeof(struct Record));
    node->zone_id = zone_id;
    node->team_id = team_id;
    node->supplies_used = supplies_used;
    node->left_record = node->right_record = NULL;
    return node;
}

void insert_record(struct Record** root, int zone_id, int team_id, struct Supplies supplies_used) {
    if (*root == NULL) {
        *root = create_record_node(zone_id, team_id, supplies_used);
        return;
    }

    if (zone_id < (*root)->zone_id) {
        insert_record(&((*root)->left_record), zone_id, team_id, supplies_used);
    } else {
        insert_record(&((*root)->right_record), zone_id, team_id, supplies_used);
    }
}
/* done by Thanav venkat reddy*/
void update_supplies(struct Supplies* team_supplies, struct Supplies* used_supplies) {
    team_supplies->food -= used_supplies->food;
    team_supplies->first_aid_kits -= used_supplies->first_aid_kits;
    team_supplies->water -= used_supplies->water;
    team_supplies->clothing -= used_supplies->clothing;
}

void assign_team_to_zone(struct Team* team, struct Zone* zone) {
    if (team) {
        struct Supplies used_supplies = zone->needed_supplies;
        update_supplies(&team->available_supplies, &used_supplies);
        insert_record(&record_tree_root, zone->zone_id, team->team_id, used_supplies);
        printf("Team %d assigned to Zone %d\n", team->team_id, zone->zone_id);
    } else {
        printf("No team has sufficient supplies for Zone %d\n", zone->zone_id);
    }
}

void process_rescue_operations() {
    struct Zone* current_zone;

    while ((current_zone = dequeue_highest_priority_zone()) != NULL) {
        printf("Processing Zone %d (Priority: %d)\n", current_zone->zone_id, current_zone->priority_level);

        struct Team* available_team = find_team_with_supplies(&current_zone->needed_supplies);

        if (available_team != NULL) {
            assign_team_to_zone(available_team, current_zone);
            free(current_zone);
        } else {
            printf("No team available with sufficient supplies for Zone %d\n", current_zone->zone_id);
            current_zone->priority_level++;

            if (current_zone->priority_level <= LOW_PRIORITY) {
                add_zone(current_zone);
            } else {
                printf("Zone %d has exceeded max priority and will not be re-added.\n", current_zone->zone_id);
                free(current_zone);
            }
        }
    }
}

/* done by Atharva Gaikwad*/
void display_zones() {
    struct Zone* current = first_zone;
    printf("\n--- Zone Status ---\n");
    while (current != NULL) {
        printf("Zone ID: %d, Priority: %d, People in need: %d\n", current->zone_id, current->priority_level, current->people_in_need);
        printf("Supplies needed - Food: %d, First Aid: %d, Water: %d, Clothing: %d\n", 
               current->needed_supplies.food, current->needed_supplies.first_aid_kits, 
               current->needed_supplies.water, current->needed_supplies.clothing);
        current = current->next_zone;
    }
}

void display_teams() {
    struct Team* current = first_team;
    printf("\n--- Team Status ---\n");
    while (current != NULL) {
        printf("Team ID: %d\n", current->team_id);
        printf("Available supplies - Food: %d, First Aid: %d, Water: %d, Clothing: %d\n", 
               current->available_supplies.food, current->available_supplies.first_aid_kits, 
               current->available_supplies.water, current->available_supplies.clothing);
        current = current->next_team;
    }
}

void display_rescue_records(struct Record* root) {
    if (root != NULL) {
        display_rescue_records(root->left_record);
        printf("Zone ID: %d, Team ID: %d\n", root->zone_id, root->team_id);
        printf("Supplies used - Food: %d, First Aid: %d, Water: %d, Clothing: %d\n", 
               root->supplies_used.food, root->supplies_used.first_aid_kits, 
               root->supplies_used.water, root->supplies_used.clothing);
        display_rescue_records(root->right_record);
    }
}

void input_zone() {
    struct Zone* new_zone = (struct Zone*) malloc(sizeof(struct Zone));
    printf("Enter Zone ID: ");
    scanf("%d", &new_zone->zone_id);
    printf("Enter Priority (1-5): ");
    scanf("%d", &new_zone->priority_level);
    printf("Enter people in need: ");
    scanf("%d", &new_zone->people_in_need);
    printf("Enter required supplies - Food: ");
    scanf("%d", &new_zone->needed_supplies.food);
    printf("First Aid: ");
    scanf("%d", &new_zone->needed_supplies.first_aid_kits);
    printf("Water: ");
    scanf("%d", &new_zone->needed_supplies.water);
    printf("Clothing: ");
    scanf("%d", &new_zone->needed_supplies.clothing);
    new_zone->next_zone = NULL;
    add_zone(new_zone);
    printf("Zone added successfully!\n");
}

void input_team() {
    struct Team* new_team = (struct Team*) malloc(sizeof(struct Team));
    printf("Enter Team ID: ");
    scanf("%d", &new_team->team_id);
    printf("Enter available supplies - Food: ");
    scanf("%d", &new_team->available_supplies.food);
    printf("First Aid: ");
    scanf("%d", &new_team->available_supplies.first_aid_kits);
    printf("Water: ");
    scanf("%d", &new_team->available_supplies.water);
    printf("Clothing: ");
    scanf("%d", &new_team->available_supplies.clothing);
    new_team->next_team = NULL;
    add_team(new_team);
    printf("Team added successfully!\n");
}



/*done by austin dcosta*/
void update_zone(int zone_id) {
    struct Zone* current = first_zone;
    
    while (current != NULL && current->zone_id != zone_id) {
        current = current->next_zone;
    }

    if (current == NULL) {
        printf("Zone with ID %d not found.\n", zone_id);
        return;
    }

    printf("Enter new people in need: ");
    scanf("%d", &current->people_in_need);

    printf("Enter updated supplies needed - Food: ");
    scanf("%d", &current->needed_supplies.food);
    printf("First Aid: ");
    scanf("%d", &current->needed_supplies.first_aid_kits);
    printf("Water: ");
    scanf("%d", &current->needed_supplies.water);
    printf("Clothing: ");
    scanf("%d", &current->needed_supplies.clothing);

    printf("Zone updated successfully!\n");

 
}


void update_team(int team_id) {
    struct Team* current = first_team;
    while (current != NULL && current->team_id != team_id) {
        current = current->next_team;
    }

    if (current == NULL) {
        printf("Team with ID %d not found.\n", team_id);
        return;
    }

    printf("Enter updated available supplies - Food: ");
    scanf("%d", &current->available_supplies.food);
    printf("First Aid: ");
    scanf("%d", &current->available_supplies.first_aid_kits);
    printf("Water: ");
    scanf("%d", &current->available_supplies.water);
    printf("Clothing: ");
    scanf("%d", &current->available_supplies.clothing);
    printf("Team updated successfully!\n");
}

void remove_zone(int zone_id) {
    struct Zone* current = first_zone;
    struct Zone* previous = NULL;

    while (current != NULL && current->zone_id != zone_id) {
        previous = current;
        current = current->next_zone;
    }

    if (current == NULL) {
        printf("Zone with ID %d not found.\n", zone_id);
        return;
    }

    if (previous == NULL) {
        first_zone = current->next_zone;
    } else {
        previous->next_zone = current->next_zone;
    }
    
    free(current);
    printf("Zone with ID %d removed successfully.\n", zone_id);
}

/* done by Aviyalth Rai */
void remove_team(int team_id) {
    if (first_team == NULL) {  
        printf("The team list is empty.\n");
        return;
    }
    
    struct Team* current = first_team;
    struct Team* previous = NULL;

    while (current != NULL && current->team_id != team_id) {
        previous = current;
        current = current->next_team;
    }

    if (current == NULL) {  
        printf("Team with ID %d not found.\n", team_id);
        return;
    }

    if (previous == NULL) {  
        first_team = current->next_team;
    } else {  
        previous->next_team = current->next_team;
    }
    
    free(current); 
    current = NULL; 
    printf("Team with ID %d removed successfully.\n", team_id);
}


int main() {
    int choice, id;

    do {
        printf("\n--- Rescue Operation Management ---\n");
        printf("1. Add Zone\n");
        printf("2. Add Team\n");
        printf("3. Process Rescue Operations\n");
        printf("4. Display Zones\n");
        printf("5. Display Teams\n");
        printf("6. Display Rescue Records\n");
        printf("7. Update Zone\n");
        printf("8. Update Team\n");
        printf("9. Remove Zone\n");
        printf("10. Remove Team\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                input_zone();
                break;
            case 2:
                input_team();
                break;
            case 3:
                process_rescue_operations();
                break;
            case 4:
                display_zones();
                break;
            case 5:
                display_teams();
                break;
            case 6:
                printf("\n--- Rescue Records ---\n");
                display_rescue_records(record_tree_root);
                break;
            case 7:
                printf("Enter Zone ID to update: ");
                scanf("%d", &id);
                update_zone(id);
                break;
            case 8:
                printf("Enter Team ID to update: ");
                scanf("%d", &id);
                update_team(id);
                break;
            case 9:
                printf("Enter Zone ID to remove: ");
                scanf("%d", &id);
                remove_zone(id);
                break;
            case 10:
                printf("Enter Team ID to remove: ");
                scanf("%d", &id);
                remove_team(id);
                break;
            case 11:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 11);

    return 0;
}
