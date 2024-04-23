#pragma once

// This file includes structs and functions related to the players and party

#include "area.h"
#include "item.h"

// enum that represents the general state of the game
enum Game_State {
    Won,
    Lost,
    Playing
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
    Player* p0;
    Player* p1;
    Player* p2;
    Player* p3;
};

// linked list that represents a player's inventory
struct Inventory {
    Item* item;
    Inventory* next;
};

// represents a class
enum Role {
    Archer,
    Warrior,
    Mage,

    // not used for player role; only for items
    Anyone 
};

// character creation (prompts for player choices form ui.h)
Party* create_characters();

// delete the party
Party* delete_party(Party*);

// check whether a player has a specific item type
bool player_has_item(Player*, Item_Type);

// get the effect value (damage, healing, etc.) done by an item
int get_item_effect_value(Item_Type);