#include "player.h"
#include "area.h"
#include "ui.h"

#include <cstdlib>
#include <cstdio>

void delete_inventory(Inventory*);

Party* create_characters() {
    Party* party = new Party();
    party->location = Area::Town;
    party->num_enemies = 0;

    printf("Enter the number of players [1-4]: ");
    int num_players = get_menu_choice("1234") - '0'; // convert char number to int
    puts("");

    for(int i = 0; i < num_players; i++) {
        Player* p = new Player();

        // get the player's name
        printf("Player %d, enter your name: ", i);
        p->name = get_string(15);
        puts("");

        // print and get the player's role
        puts("Role Options:");
        puts("\t[a] Archer");
        puts("\t[w] Warrior");
        puts("\t[m] Mage");
        printf("%s, select your role: ", p->name);
        p->role = (Role)(get_menu_choice("awm") - '0');

        // set the player health and add the role's main weapon
        p->health = get_role_health(p->role);
        add_to_inventory(p, (Item_Type)(int)p->role); // main weapons correspond to same numbers as roles

        // add it to the correct player
        switch(i) {
            case 0: party->p0 = p;
            case 1: party->p1 = p;
            case 2: party->p2 = p;
            case 3: party->p3 = p;
        }
    }

    // return the created party
    return party;
}

Party* delete_party(Party* party) {
    for(int i = 0; i < 4; i++) {
        Player* p_to_delete = get_player_number(i);

        if(p_to_delete == nullptr) {
            continue;
        }

        delete p_to_delete->name;
        p_to_delete->name = nullptr;
        delete_inventory(p_to_delete->inv);
        p_to_delete->inv = nullptr;
        delete p_to_delete;
        p_to_delete = nullptr;
    }

    party->p0 = nullptr;
    party->p1 = nullptr;
    party->p2 = nullptr;
    party->p3 = nullptr;
}

int player_num_items(Player* player, Item_Type item) {

}

Player* get_player_number(Party* party, int num) {
    switch(num) {
        case 0: return party->p0;
        case 1: return party->p1;
        case 2: return party->p2;
        case 3: return party->p3;
    }
}

void add_to_inventory(Player* player, Item_Type item) {
    
}

void remove_from_inventory(Player* player, Item_Type item) {
    
}

void delete_inventory(Inventory* inv) {
    Inventory* to_del = inv;
    Inventory* next = nullptr;

    while(inv->next != nullptr) {
        next = inv->next;

        delete inv;

        inv = next;
    }
}