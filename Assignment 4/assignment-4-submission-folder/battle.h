#pragma once

// This file contains the battle functions

#include "item.h"

// Enemy struct
struct Enemy {
    const char* name;
    const char* description;
    int damage;
    int health;
};

enum Enemy_Type {
    Shrimp,
    Mosquito,
    Mimic,
    Dragon
};

// get an enemy based on its type
Enemy* get_enemy_of_type(Enemy_Type);

// delete an enemy
Enemy* delete_enemy(Enemy*);

// mineshaft battle function
void mineshaft_battle();

// castle battle function
void castle_battle();