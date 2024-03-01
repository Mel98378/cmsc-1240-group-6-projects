/*
    Assignment 2: Using Arrays in Battle
    Authors: Group 6

    main() on line 113


    Project Requirements:
    ---------------------
    1) Character creation
        - Each player can choose their name and class
    2) Gameplay (encounters)
        - Battles, other decisions
        - Each encounter presents the players with options,
          have appropriate outcomes
    3) Combat system
        - Simple; players and enemies have HP and can deal damage
        - Must store information (names, classes, HP, damage, etc) 
          in parallel arrays
    4) Inventory and items
        - Basic system that allows gaining and using items
        - Must use parallel arrays to store information (names, descriptions, effects, etc)
    5) Random events
        - Use random generators/basic logic structures
    6) Game over/win conditions
        - Winning: defeating the dragon
        - Losing: dying
        - Include appropriate message for game state
    7) Other requirements
        - Adequate error handling
        - Clear or intuitive UI
        - Document your code (write comments)
        - Keep the mechanics simple and the scope small


    Contributions:
    --------------
        Camron:
        Evan:
        Lavender: file setup and specs, constants setup, main(), character_creation(), get_num_players(), 
                  validate_input(), print_input_error(), print_game_information(), player_choose_info(),
                  print_class_choice()
        Teddy: 
    
    
    Naming Conventions (please follow):
    -----------------------------------
    methods, functions, and (mutable) variables: snake_case
    constants: SCREAMING_SNAKE_CASE
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <regex>
#include <functional>
#include <conio.h>
using namespace std;

// player data
const int MAX_PLAYERS = 4; // per game
const int MAX_ITEMS_EACH = 3; // per player
int num_players;
char* player_names[MAX_PLAYERS];
int player_hp[MAX_PLAYERS]; // current player hp 
int player_class[MAX_PLAYERS];
int player_damage[MAX_PLAYERS]; // current player damage (affected by items)

// class data
/* 
    attack information:
    -------------------
    each attack for any class deals whatever the player's
    current damage is to the enemy
*/
const int NUM_CLASSES = 3;
const char* CLASS_TYPES[NUM_CLASSES] = {"archer", "swordsman", "alchemist"};
const int CLASS_BASE_DAMAGE[NUM_CLASSES] = {10, 10, 5};
const int CLASS_BASE_HEALTH[NUM_CLASSES] = {30, 40, 20};
const char* ARCHER_ATTACKS[] = {"shoot", "stab"};
const char* SWORDSMAN_ATTACKS[] = {"slash", "poke"};
const char* ALCHEMIST_ATTACKS[] = {"splash poison", "heal"}; /* the alchemist is not very good 
                                                                at healing (does damage) */

// item data
/* 
    item descriptions:
    ------------
    health potion: consumable, heals
    vitamin gummy: consumable, increases damage permanently
    rock: throwable, causes damage
    big rock: throwable, causes big damage

    item information:
    -----------------
    items can only be used once ever (to keep system simple)
    each player starts off with all 4 items
*/
const int NUM_ITEMS = 4;
const char* ITEMS[NUM_ITEMS] = {"health potion", "vitamin gummy", "rock", "big rock"};
const char* ITEM_DESCRIPTIONS[NUM_ITEMS] = {"heals 10 hp", "increases damage by 10",
                                            "causes 5 hp of damage", "causes 20 hp of damage"};
const int ITEM_EFFECTS[NUM_ITEMS] = {10, 10, 5, 20};
bool player_one_items[NUM_ITEMS] = {true, true, true, true};
bool player_two_items[NUM_ITEMS] = {true, true, true, true};
bool player_three_items[NUM_ITEMS] = {true, true, true, true};
bool player_four_items[NUM_ITEMS] = {true, true, true, true};


// enemy data
/*
    location info:
    ----------
    dragon: castle
    fish, mosquito, mimic: mineshaft
*/
const int MAX_ENEMIES = 4; // per encounter
const char* ENEMY_TYPES[MAX_ENEMIES] = {"dragon", "shrimp", "mosquito", "mimic"};
int enemy_hp[MAX_ENEMIES] = {100, 5, 30, 40};
int enemy_damage[MAX_ENEMIES] = {30, 100, 10, 10};

// location data
/*
    location information:
    ---------------------
    town
        - starting location
        - can talk and get information
        - can travel to mineshaft or castle
    mineshaft
        - can kill random enemies
        - can return to town between battles
        - can die and lose
    castle
        - must kill at least 1 enemy in mineshaft to enter
        - fight dragon
        - can kill dragon and win
        - can die and lose
*/
const char* LOCATIONS[] = {"town", "mineshaft", "castle"};
const char* LOCATION_DESCRIPTIONS[] = {"TODO", "TODO", "TODO"};

// all function prototypes
void character_creation();
void get_num_players();
int validate_input(regex, string, function<bool(int)>);
void print_input_error(string, string);
void print_game_information();
void player_choose_info();
void print_class_choice();

//bool game_loop();
//void win_screen();
//void lose_screen();

int main() {
    // set random seed
    srand(time(nullptr));

    // create characters
    character_creation();

    // play the game; if win or lose conditions met, 
    // execute the respective result
    //if(game_loop()) win_screen();
    //else lose_screen();
}

void character_creation() {
    get_num_players();
    print_game_information();
    print_class_choice();
    player_choose_info();

}

void get_num_players() {
    cout << "\n\nEnter the number of players [1-4]: ";
    regex reg("[0-9]");
    string condition_str = "an integer at least 1 and at most 4";
    function<bool(int)> conditions = [](int x) {return (x >= 1 && x <= 4);};
    num_players = validate_input(reg, condition_str, conditions);
}

// regex match and check conditions
int validate_input(regex desired, string condition_str, function<bool(int)> conditions) {
    string input;
    int num;
    do {
        cin >> input;
        if(!regex_match(input, desired)) {
            print_input_error(input, condition_str);
            continue;
        }
        num = stoi(input); // can only cast to int once we know it's safe to do so

        // check for specified bounds
        if(!conditions(num)) {
            print_input_error(input, condition_str);
            continue;
        }
        break;
    } while(true);

    return num;
}

void print_input_error(string input, string condition_str) {
    cout << "\"" << input << "\" is not a valid choice." << endl
         << "Input must be " << condition_str << "." << endl
         << "Enter a valid choice: ";
}

void print_game_information() {
    cout << "\n\nClass information:" << endl
         << "------------------" << endl;
    for(int i = 0; i < 3; i++) {
        cout << CLASS_TYPES[i] << endl
             << "\t- base health: " << CLASS_BASE_HEALTH[i] << endl
             << "\t- base damage: " << CLASS_BASE_DAMAGE[i] << endl;
    }

    cout << "\nPress any key to continue.";
    getch();

    cout << "\n\nPlayer information:" << endl
         << "----------------------" << endl
         << "Each player starts out with 4 items:" << endl;
    for(int i = 0; i < NUM_ITEMS; i++) {
        cout << "\t -" << ITEMS[i] << ": " << ITEM_DESCRIPTIONS[i] << endl;
    }
    cout << "Once you use an item, you cannot use it again." << endl
         << "To win, defeat the dragon in the castle." << endl
         << "If all party members die, you lose." << endl
         << "Good luck." << endl;

    cout << "\nPress any key to continue.";
    getch();
}

void player_choose_info() {
    regex reg("[0-9]");
    string condition_str = "an integer at least 0 and at most 2";
    function<bool(int)> condition = [](int x) {return (x >= 0 && x <=2);};

    // TODO: add name input 
    // gotta figure out how to get a string to a fixed-size 
    // array of chars in a safe way 
}

void print_class_choice() {
    cout << "\n\nClass options: " << endl;
    for(int i = 0; i < NUM_CLASSES; i++) {
        cout << "\t[" << i << "] " << CLASS_TYPES[i] << endl;
    }
}