#ifndef ITEM_H
#define ITEM_H

// This file contains structs and functions related to items

#include "role.h"

enum Role;

// main weapons can only be used by specific roles;
// all others can be used by anyone
enum Item_Type {
    // main weapons that only specific roles can use (0-2)
    Bow,
    Sword,
    Staff,

    // items anyone can use (3-6)
    Health_Potion,
    Vitamin,
    Rock,
    Big_Rock
};

// need to be able to get name, description, damage/effect,
// and user of each item type
/*
    description:
    ------------
    write names, descriptions, effect values, and users
    for each of the above item types; then,
    use switch statements in each of these functions 
    to return the relevant information to each item type.
*/
char* get_item_name(Item_Type);
char* get_item_desc(Item_Type);
int get_item_effect(Item_Type);
Role get_item_user(Item_Type);

#endif