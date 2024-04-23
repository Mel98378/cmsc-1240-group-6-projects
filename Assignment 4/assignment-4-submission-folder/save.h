#pragma once

// this file contains everything related to saving and loading
// there will be 3 save slots, can only save/load at specific points

#include "player.h"

// struct that contains a snapshot of the party
// includes location, items, health, names, etc.
/*
    save/load points: at the beginning of each area
    ()
*/
struct Save_Data {
    Party* party_state;
};

// gets the data from a save slot (1-3)
Save_Data* get_save_data(int);

void load_save_data();

// makes or overwrites a save slot (given a save slot; 1, 2, or 3)
void save_game(int);

/*
    save data file will be a text file named savedata.txt; the format will look like this:
    (brackets as delimiters, the previous character giving it meaning; custom items will be lost)
    ------------

    1{ (slot One)
        l{(location)}
        0{ (player 0)
            n{(name: string)}
            i{ (inventory)
                t{(item type: char)}
                ... (other items)
            }
            r{(role: char)}
            h{(health: int)}
        }
        ... (other players)
    }
    ... (other slots)

    ------------
    in the final version this will be condensed, and only 
    navigated using brace counting (levels of nesting) and the 
    chars that precede each opening brace    

*/