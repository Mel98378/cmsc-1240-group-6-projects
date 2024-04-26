#ifndef UI_H
#define UI_H

// this file contains all input functions for the players

// menu navigation by getting a character from the user
// feed this function a string literal (const char*) of the valid choices
// (eg. "sl" for [s]aving and [l]oading)
char get_menu_choice(const char*); 

// gets a string from the user given a max size
// (size given does not inlcude the null terminator)
char* get_string(int);

// pauses the program until the user presses any key
/*
    description:
    ------------
    this function will print something like "press a key to continue...",
    and will not continue the program until a key is pressed.

    because we have a team member on mac, it is likely you'll have to 
    make one implementation for mac and one for windows;
    use `#ifdef` to check whether the system is mac (`__APPLE__`) 
    or windows (`_WIN32`), and make a function that works on the 
    appropriate system.
*/
void wait_until_key();

#endif