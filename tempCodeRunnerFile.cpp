#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIGH_PRIORITY 1
#define LOW_PRIORITY 5

// Structure definitions
struct supplies {
    int food;
    int first_aid;
    int water;
    int clothes;
};

struct zone {
    int priority;
    struct supplies needed_supplies;
    int people_inneed;
    int id;
    struct zone* next;
};

struct team {
    struct supplies team_supplies;
    int id;
    struct team* next;
};

struct record {
    int zone_id;
    int team_id;
    struct supplies used_supplies;  // Track supplies used in each rescue
    struct record* left;
    struct record* right;
};

// Global variables for managing lists and records
struct zone* zone_head = NULL;
struct team* team_head = NULL;
struct record* rescue_record_tree = NULL;

// Priority Queue Functions for Zones
void add_zone(struct zone* new_zone) {
    struct zone* current;
    struct zone* prev = NULL;

    if (zone_head == NULL || zone_head->priority > new_zone->priority) {
        new_zone->next = zone_head;
        zone_head = new_zone;
        return;
    }

    current = zone_head;
    while (current != NULL && current->priority <= new_zone->priority) {
        prev = current;
        current = current->next;
    }

    prev->next = new_zone;
    new_zone->next = current;
}

struct zone* get_highest_priority_zone() {
    if (zone_head == NULL) return NULL;

    struct zone* highest = zone_head;
    zone_head = zone_head->next;
    highest->next = NULL;
    return highest;
}

// Team Management Functions
void add_team(struct team* new_team) {
    new_team->next = team_head;
    team_head = new_team;
}

struct team* find_team_with_supplies(struct supplies* needed_supplies) {
    struct team* current = team_head;
    while (current != NULL) {
        if (current->team_supplies.food >= needed_supplies->food &&
            current->team_supplies.first_aid >= needed_supplies->first_aid &&
            current->team_supplies.water >= needed_supplies->water &&
            current->team_supplies.clothes >= needed_supplies->clothes) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Record Management Functions (BST for Rescue Records)
struct record* create_record_node(int zone_id, int team_id, struct supplies used_supplies) {
    struct record* node = (struct record*)malloc(sizeof(struct record));
    node->zone_id = zone_id;
    node->team_id = team_id;
    node->used_supplies = used_supplies;  // Store the supplies used
    node->left = node->right = NULL;
    return node;
}

void insert_record(struct record** root, int zone_id, int team_id, struct supplies used_supplies) {
    if (*root == NULL) {
        *root = create_record_node(zone_id, team_id, used_supplies);
        return;
    }

    if (zone_id < (*root)->zone_id) {
        insert_record(&((*root)->left), zone_id, team_id, used_supplies);
    } else {
        insert_record(&((*root)->right), zone_id, team_id, used_supplies);
    }
}

// Supply Management Functions
void update_supplies(struct supplies* team_supplies, struct supplies* used_supplies) {
    team_supplies->food -= used_supplies->food;
    team_supplies->first_aid -= used_supplies->first_aid;
    team_supplies->water -= used_supplies->water;
    team_supplies->clothes -= used_supplies->clothes;
}

// Rescue Operation Functions
void assign_team_to_zone(struct team* team, struct zone* zone) {
    if (team) {
        struct supplies used_supplies = zone->needed_supplies;  // Supplies used in this assignment
        update_supplies(&team->team_supplies, &used_supplies);
        insert_record(&rescue_record_tree, zone->id, team->id, used_supplies);  // Pass used_supplies
        printf("Team %d assigned to Zone %d\n", team->id, zone->id);
    } else {
        printf("No team has sufficient supplies for Zone %d\n", zone->id);
    }
}

void process_rescue_operations() {
    struct zone* current_zone;

    while ((current_zone = get_highest_priority_zone()) != NULL) {
        printf("Processing Zone %d (Priority: %d)\n", current_zone->id, current_zone->priority);

        struct team* available_team = find_team_with_supplies(&current_zone->needed_supplies);

        if (available_team != NULL) {
            assign_team_to_zone(available_team, current_zone);
            free(current_zone);  // Free memory as the zone has been processed
        } else {
            printf("No team available with sufficient supplies for Zone %d\n", current_zone->id);
            current_zone->priority++;

            // Re-add zone to the list only if priority is within allowed range
            if (current_zone->priority <= LOW_PRIORITY) {
                add_zone(current_zone);  // Re-add zone with updated priority
            } else {
                printf("Zone %d has exceeded max priority and will not be re-added.\n", current_zone->id);
                free(current_zone);  // Free memory as the zone cannot be reprocessed
            }
        }
    }
}


// Display Functions
void display_zones() {
    struct zone* current = zone_head;
    printf("\n--- Zone Status ---\n");
    while (current != NULL) {
        printf("Zone ID: %d, Priority: %d, People in need: %d\n", current->id, current->priority, current->people_inneed);
        printf("Supplies needed - Food: %d, First Aid: %d, Water: %d, Clothes: %d\n", 
               current->needed_supplies.food, current->needed_supplies.first_aid, 
               current->needed_supplies.water, current->needed_supplies.clothes);
        current = current->next;
    }
}

void display_teams() {
    struct team* current = team_head;
    printf("\n--- Team Status ---\n");
    while (current != NULL) {
        printf("Team ID: %d\n", current->id);
        printf("Available supplies - Food: %d, First Aid: %d, Water: %d, Clothes: %d\n", 
               current->team_supplies.food, current->team_supplies.first_aid, 
               current->team_supplies.water, current->team_supplies.clothes);
        current = current->next;
    }
}

void display_rescue_records(struct record* root) {
    if (root != NULL) {
        display_rescue_records(root->left);
        printf("Zone ID: %d, Team ID: %d\n", root->zone_id, root->team_id);
        printf("Supplies used - Food: %d, First Aid: %d, Water: %d, Clothes: %d\n", 
               root->used_supplies.food, root->used_supplies.first_aid, 
               root->used_supplies.water, root->used_supplies.clothes);
        display_rescue_records(root->right);
    }
}

// User Input Functions
void input_zone() {
    struct zone* new_zone = (struct zone*) malloc(sizeof(struct zone));
    printf("Enter Zone ID: ");
    scanf("%d", &new_zone->id);
    printf("Enter Priority (1-5): ");
    scanf("%d", &new_zone->priority);
    printf("Enter people in need: ");
    scanf("%d", &new_zone->people_inneed);
    printf("Enter required supplies - Food: ");
    scanf("%d", &new_zone->needed_supplies.food);
    printf("First Aid: ");
    scanf("%d", &new_zone->needed_supplies.first_aid);
    printf("Water: ");
    scanf("%d", &new_zone->needed_supplies.water);
    printf("Clothes: ");
    scanf("%d", &new_zone->needed_supplies.clothes);
    new_zone->next = NULL;
    add_zone(new_zone);
    printf("Zone added successfully!\n");
}

void input_team() {
    struct team* new_team = (struct team*) malloc(sizeof(struct team));
    printf("Enter Team ID: ");
    scanf("%d", &new_team->id);
    printf("Enter available supplies - Food: ");
    scanf("%d", &new_team->team_supplies.food);
    printf("First Aid: ");
    scanf("%d", &new_team->team_supplies.first_aid);
    printf("Water: ");
    scanf("%d", &new_team->team_supplies.water);
    printf("Clothes: ");
    scanf("%d", &new_team->team_supplies.clothes);
    new_team->next = NULL;
    add_team(new_team);
    printf("Team added successfully!\n");
}


// Main Function with User Menu
int main() {
    int choice;

    do {
        printf("\n--- Rescue Operation Management ---\n");
        printf("1. Add Zone\n");
        printf("2. Add Team\n");
        printf("3. Process Rescue Operations\n");
        printf("4. Display Zones\n");
        printf("5. Display Teams\n");
        printf("6. Display Rescue Records\n");
        printf("7. Exit\n");
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
                display_rescue_records(rescue_record_tree);
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
