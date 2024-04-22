#pragma once

// this file contains everything related to saving and loading
// there will be 3 save slots, can only save/load at specific points

#include "area.h"
#include "player.h"

// struct that contains a snapshot of the party
// includes location, items, health, names, etc.
struct Save_Data {
    Party* party_state;
};

// gets the data from a save
Save_Data* load_from_save();

// makes or overwrites a save slot
void save_game();

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

*/