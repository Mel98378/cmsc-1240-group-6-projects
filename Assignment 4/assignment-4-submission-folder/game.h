#pragma once

// contains the start of the game;
// this function will link most of the other header files together 
// to make the game playable

#include "player.h"

// starts the main game loop; if there is no party created,
// go to character creation; otherwise, a save is being loaded
void start_game(Party*);

// win and lose screens
void game_won_screen();
void game_over_screen();