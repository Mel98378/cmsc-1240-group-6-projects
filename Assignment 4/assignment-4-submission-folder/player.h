#pragma once

// This file includes structs and functions related to the players and party

#include "area.h"
#include "item.h"
#include "role.h"

// enum that represents the general state of the game
enum Game_State {
    Won,
    Lost,
    Playing
};

// linked list that represents a player's inventory
struct Inventory {
    Item_Type item;
    Inventory* next;
};


// struct that represents a player
struct Player {
    char* name;
    Inventory* inv;
    Role role;
    int health;
};

// struct that represents the party (1-4 players)
struct Party {
    Area location; // used to determine the next location of the party
    Game_State state;
    int num_enemies; // number of enemies defeated
    Player* p0;
    Player* p1;
    Player* p2;
    Player* p3;
};
// character creation (prompts for player choices form ui.h)
/*
    description:
    ------------
    after determining how many players there will be, 
    get the names and roles of each player, initialize their
    inventories, and initialize the other party information.
*/
Party* create_characters();

// delete the party
/*
    description:
    ------------
    deletes the party. must start with the smallest unfreed memory first,
    moving up as levels of memory are freed.
*/
Party* delete_party(Party*);

// check whether a player has a specific item type
/*
    description:
    ------------
    returns how many of a specific item any player has.
*/
int player_num_items(Player*, Item_Type);

// returns the player with the specified number
Player* get_player_number(int);

// functions to add and remove items from player inventories
void add_to_inventory(Player*, Item_Type);
void remove_from_inventory(Player*, Item_Type);