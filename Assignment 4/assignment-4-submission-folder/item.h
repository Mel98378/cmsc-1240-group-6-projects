#pragma once

// This file contains structs and functions related to items

#include "player.h" // for roles

// general item struct for any particular items
struct Item {
    char* name;
    char* description;

    // (amount to damage, heal, etc.)
    int effect_value;

    // determines both who can use the item
    Role user; 
};

enum Item_Type {
    Health_Potion,
    Vitamin,
    Rock,
    Big_Rock
};

// make an item based on its type
Item* get_item_of_type(Item_Type);

// get the main weapons for the player roles
Item* get_bow();
Item* get_sword();
Item* get_staff();

// delete an item
Item* delete_item(Item*);