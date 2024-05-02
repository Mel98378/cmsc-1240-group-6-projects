#include "player.h"
#include "area.h"
#include "ui.h"

#include <cstdlib>
#include <cstdio>

void delete_inventory(Inventory*);

// character creation logic
//MARK: create_characters()
Party* create_characters() {
    Party* party = (Party*) malloc(sizeof(Party));
    party->location = Area::Town;
    party->state = Game_State::Playing;
    party->num_enemies = 0;

    printf("Enter the number of players [1-4]: ");
    int num_players = get_menu_choice("1234") - '0'; // convert char number to int
    puts("");

    for(int i = 0; i < num_players; i++) {
        Player* p = (Player*) malloc(sizeof(Player));

        // get the player's name
        printf("Player %d, enter your name: ", i);
        p->name = get_user_name();
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
        party->players[i] = p;
    }

    // return the created party
    return party;
}

// delete the party
//MARK: delete_party()
Party* delete_party(Party* party) {
    for(int i = 0; i < 4; i++) {
        Player* p_to_delete = party->players[i];

        if(p_to_delete == nullptr) {
            continue;
        }

        free(p_to_delete->name);
        p_to_delete->name = nullptr;
        delete_inventory(p_to_delete->inv);
        p_to_delete->inv = nullptr;
        free(p_to_delete);
        p_to_delete = nullptr;
    }

    for(int i = 0; i < 4; i++) {
        party->players[i] = nullptr;
    }

    return party;
}

// returns the number of a specific item type any player has
//MARK: player_num_items()
int player_num_items(Player* player, Item_Type item) {

}

// adds an item to a player's inventory
//MARK: add_to_inventory()
void add_to_inventory(Player* player, Item_Type item) {
    
}

// removes an item from a player's inventory
//MARK: remove_from_inventory()
void remove_from_inventory(Player* player, Item_Type item) {
    
}

// deletes a player's inventory
//MARK: delete_inventory()
void delete_inventory(Inventory* inv) {
    Inventory* to_del = inv;
    Inventory* next = nullptr;

    while(to_del->next != nullptr) {
        next = to_del->next;
        free(to_del);
        to_del = next;
    }
}