#ifndef GAME_H
#define GAME_H

// contains the start of the game;
// this function will link most of the other header files together 
// to make the game playable

// starts the main game loop; if there is no party created,
// go to character creation; otherwise, a save is being loaded
/*
    description:
    ------------
    ask if the players want to load from a save; if they do,
    check for the save and load it if possible. 

    otherwise, create a new party and start the game loop

    the loop must determine where the party goes next based on the 
    party->location field inside the party struct.
*/
void start_game();

#endif