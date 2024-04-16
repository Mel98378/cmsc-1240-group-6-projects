#pragma once
// This file contains structs and functions related to items

#include "player.h"

struct Item {
    char* name;
    char* description;

    // (amount to damage, heal, etc.)
    int effect_value;

    // determines both who can use the item and
    // whether the item can be used multiple times
    // (Role::Anyone items are single-use only)
    Role user; 
};

Item* new_item(const char*, const char*, int, Role);
Item* delete_item(Item*);