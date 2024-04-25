#pragma once

// contains the start of the game;
// this function will link most of the other header files together 
// to make the game playable

#include "player.h"

// starts the main game loop; if there is no party created,
// go to character creation; otherwise, a save is being loaded
/*
    description:
    ------------
    if nullptr is fed, then the game is a new one;
    create the characters, and call town() before the main loop. 

    if an existing party is fed, then the game is being loaded from
    a save; ignore character creation and the first town() call,
    and go straight into the loop.

    the loop must determine where the party goes next based on the 
    party->location field inside the party struct.
*/
void start_game(Party*);

// win and lose screens
/*
    description:
    ------------
    print whether the party has won or lost.
*/
void game_won_screen();
void game_over_screen();