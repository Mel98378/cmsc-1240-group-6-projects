#pragma once

// this file contains everything related to saving and loading
// there will be 3 save slots, can only save/load at specific points

// gets the data from the save file; if there is no data,
// default to creating new characters
Party* get_save_data();

// makes or overwrites a save file
void save_game();

/*
    save data file will be a text file named savedata.txt; the format will look like this:
    ------------

    location=%d
    enemies=%d
    p0=name:%s inv:%s role:%d health:%d
    p1=name:%s inv:%s role:%d health:%d
    p2=name:%s inv:%s role:%d health:%d
    p3=name:%s inv:%s role:%d health:%d

    ------------
    
    if a player's name is an empty string {'\0'}, then the player does not exist
*/