#ifndef RESCUE_OPERATIONS_H
#define RESCUE_OPERATIONS_H

#define HIGH_PRIORITY 1
#define LOW_PRIORITY 5

/* done by ALL four of us*/
struct Supplies {
    int food;
    int first_aid_kits;
    int water;
    int clothing;
};

struct Zone {
    int priority_level; // fixed the typo here: removed extra '4'
    struct Supplies needed_supplies;
    int people_in_need;
    int zone_id;
    struct Zone* next_zone;
};

struct Team {
    struct Supplies available_supplies;
    int team_id;
    struct Team* next_team;
};

struct Record {
    int zone_id;
    int team_id;
    struct Supplies supplies_used;
    struct Record* left_record;
    struct Record* right_record;
};

extern struct Zone* first_zone;
extern struct Team* first_team;
extern struct Record* record_tree_root;

void add_zone(struct Zone* new_zone);
struct Zone* dequeue_highest_priority_zone();
void add_team(struct Team* new_team);
struct Team* find_team_with_supplies(struct Supplies* required_supplies);
struct Record* create_record_node(int zone_id, int team_id, struct Supplies supplies_used);
void insert_record(struct Record** root, int zone_id, int team_id, struct Supplies supplies_used);
void update_supplies(struct Supplies* team_supplies, struct Supplies* used_supplies);
void assign_team_to_zone(struct Team* team, struct Zone* zone);
void process_rescue_operations();
void display_zones();
void display_teams();
void display_rescue_records(struct Record* root);
void input_zone();
void input_team();
void update_zone(int zone_id);
void update_team(int team_id);
void remove_zone(int zone_id);
void remove_team(int team_id);

#endif
