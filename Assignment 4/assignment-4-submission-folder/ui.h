#pragma once

// this file contains all input functions for the players

// menu navigation by getting a character from the user
// feed this function a string literal (const char*) of the valid choices
// (eg. "sl" for [s]aving and [l]oading)
char get_menu_choice(const char*); 

// gets a string from the user given a max size
char* get_string(int);

// pauses the program until the user presses any key
// (use for showing the user large pieces of text)
void wait_until_key();