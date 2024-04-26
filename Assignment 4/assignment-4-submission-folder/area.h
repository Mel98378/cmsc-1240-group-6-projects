#pragma once

// This file contains all the logic for the location functions

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
*/
void town();

// the mineshaft area loop
/*
    description:
    ------------
    first, send the party into a mineshaft battle.

    if the players win the battle, give each player a treasure,
    and then let the players choose to keep fighting or go to another 
    area.
    (use party->state to determine if they won or lost the battle)
*/
void mineshaft();

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
*/
void castle();