/*
    Assignment 4: Putting it Together
    Author: Group 6


    Requirements:
    -------------
    Refactor assignment 2 to meet these:
        - All parallel array structures are converted to stucts and arrays of structs
        - All uses of hard-coded indicators and flags will be convented to use enums
        - Where convinient, typedefs will be used to convey the use of particular data
        - All functions will be grouped according to their purpose in separate header
          and source files
        - All code should be properly commented, variables and functions named in a 
          logical manner, and well structured (proper indentation)
    Include a dynamic inventory system
        - Must allow any number of items to be added to the player
        - Must properly remove items from inventory
    Include a save system for the status of a player
        - Must save player's name and health at a minimum
    Include the ability to load the game from a previous playthrough 
        - Achieve this by opening and reading the save file


    Header files:
    -------------
    Game: 
        - main game loop
    Player:
        - game state enum
        - player struct
        - party struct
        - inventory struct
        - role struct
        - character creation logic
    UI: 
        - user input (after some thought, i think printing should be 
          handled by the individual source files instead of trying to generalize them)
    Battle:
        - battle systems
        - enemy structs
    Item: 
        - contains items (main battle interaction)
    Save:
        - contains functions for writing and reading save data from the file
        - reades from and writes to savedata.txt

    
    Notes:
    ------
    (lavender): just a reminder to everyone for building multifile projects: make
                sure that your header files includes all the relevant files it uses
                uses. in your terminal, cd into this folder (../assignment-4-submission-folder/),
                and run `g++ *.cpp -o main` to get the executable

    (lavender): above are just general pieces of information about what each header should
                contain, but more details are available in the files themselves. for structs
                and enums, they must be defined in the header file, but i think we should keep 
                function definitions in source files (keeping declarations in headers)

    (lavender): it was important that i got all the structs and enums set up alongside the 
                function prototypes in each header file beacuse everyone will rely on them
                being defined and having named parameters in order to actually implement
                each section of the code

    (lavender): also, for any helper functions that other header files don't need to access,
                you should only declare them in the source file and not in the header file

    
    Contributions:
    --------------
    Evan: 
    Camron: 
    Lavender: project files organization/setup
    Teddy: 


    TODO:
    -----
    reimplementations
        - main program loop [game.h] (unassigned)
        - area functions [area.h] (unassigned)
        - battle functions and enemies [battle.h] (unassigned)
        - character creation [player.h] (unassigned)
        - player inventory management [player.h] (unassigned)
        - item handling [item.h] (unassigned)
        - input [ui.h] (unassigned)
    new items
        - saving and loading [save.h] (lavender)
*/

#include "game.h"

int main() {
    start_game(nullptr);
}