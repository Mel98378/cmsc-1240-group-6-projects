#pragma once

// this file contains user interface functions

//                        ---- information printing ----
void print_game_information();
void print_role_information();


//                        ---- menu/option printing ----
void print_num_player_options();
void print_role_options();
void print_location_options();
void print_mineshaft_options(); // whether to keep fighting or to return to the town


//                        ---- input ----
// menu navigation by getting a character from the user
// only returns the user's input if it is contained in the options (pass in a string literal of options)
char get_menu_choice(char*); 

// gets a string from the user given a max size
char* get_string(int);