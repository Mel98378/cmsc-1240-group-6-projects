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

// struct that represents the party
struct Party {
    Area location;
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