#ifndef BATTLE_H
#define BATTLE_H

// This file contains the battle functions
#include "player.h"
struct Party;


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
/*
    description:
    -----------
    for each of the enemy types above, switch over the input and
    create a new enemy from scratch with the appropriate details,
    then return it.
*/
Enemy* get_enemy_of_type(Enemy_Type);

// delete an enemy
/*
    description:
    ------------
    when deleting an enemy, make sure to first free/delet the smallest
    pointer first (ex. name and description before freeing the enemy pointer).
    
    then, make sure to deal with the dangling pointer.
*/
Enemy* delete_enemy(Enemy*);

// mineshaft battle function
/*
    description:
    ------------
    simulate a singular battle against a randomized mineshaft enemy
    (you must do the randomization inside the function).

    if all the players in the party die, change the party's game state
    (to Game_State::Lost) and return.
*/

void mineshaft_battle(Party*);


// castle battle function
/*
    description:
    ------------
    simulate the fight with the dragon. 

    same lose condition as above, but if the players win, then set 
    the game state accordingly and return.
*/

void castle_battle(Party*);

#endif

