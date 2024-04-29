#ifndef AREA_H
#define AREA_H

// This file contains all the logic for the location functions

#include "player.h"

struct Party;

enum Area {
    Town,
    Mineshaft,
    Castle
};

// the town area loop
/*
    description:
    ------------
    same as the loop in the original program. allow the players to 
    choose a location to travel to (and, if you want to do something extra,
    allow the players to talk to some npcs)

    you can prompt the party to save at any point while they're here
*/
void town(Party*);

// the mineshaft area loop
/*
    description:
    ------------
    first, send the party into a mineshaft battle.

    if the players win the battle, give each player a treasure,
    and then let the players choose to keep fighting or go to another 
    area.
    (use party->state to determine if they won or lost the battle)

    you should give the party the option to save only between battles
*/
void mineshaft(Party*);

// the castle area loop
/*
    description:
    ------------
    check party->enemies_defeated for however many enemies should be
    defeated before the final boss.

    if the party doesn't have enough, let them choose another area to go to.

    if the party does have enough, let them challenge the dragon 
    (sending them into the dragon battle).

    note: you shouldn't have to have any code past when you call the castle battle function.

    you should only give the party the option to save right before starting the battle
*/
void castle(Party*);

#endif