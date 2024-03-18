/*
    Assignment 2: Using Arrays in Battle
    Authors: Group 6


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
        Camron: Combat system (battle(), dragon_battle())
        Evan:
        Lavender: file setup and specs, character_creation() and related functions, logic in start_game()
        Teddy: town(), mineshaft(), castle() setup (excluding detailed battle system), win and lose screens, movement
               between areas
    
    
    Naming Conventions (please follow):
    -----------------------------------
    methods, functions, and non-constant variables: snake_case
    constants: SCREAMING_SNAKE_CASE
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <regex>
#include <functional>
using namespace std;

// general data
bool game_over;
bool defeated_dragon;

// player data
const int MAX_PLAYERS = 4; // per game
const int MAX_ITEMS_EACH = 3; // per player
int num_players;
int party_location;
char player_names[MAX_PLAYERS][26];
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
const int MINESHAFT_ENEMIES = 3;
const char* ENEMY_TYPES[MINESHAFT_ENEMIES] = {"shrimp", "mosquito", "mimic"};
const int BASE_ENEMY_HP[MINESHAFT_ENEMIES] = {5, 30, 40};
const int BASE_ENEMY_DAMAGE[MINESHAFT_ENEMIES] = {100, 10, 10};
const int FINAL_BOSS = 1;
const char* FINAL_BOSS_TYPE[FINAL_BOSS] = {"dragon"};
int FINAL_BOSS_HP[FINAL_BOSS] = {100};
const int FINAL_BOSS_DAMAGE[FINAL_BOSS] = {30};
int current_enemy_hp;
int current_enemy_damage;

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

// character creation function prototypes
void character_creation();
void get_num_players();
int validate_input(string, regex, string, function<bool(int)>);
void print_input_error(string, string);
void print_game_information();
void player_choose_info();
void print_class_options();

// wait until any key pressed
void wait_until_key();

// game mechanics prototypes
void start_game();
void town();
void mineshaft();
void castle();

// winn and loss prototypes
void win_screen();
void lose_screen();

// Combat prototypes
void battle();
void dragon_battle();
bool defeated_enemy = false;

int main() {
    // set random seed
    srand(time(nullptr));

    // clear the terminal
    system("cls");

    // create characters
    character_creation();

    //start the game loop
    start_game();
}

void character_creation() {
    get_num_players();
    print_game_information();
    player_choose_info();

}

void get_num_players() {
    string message = "Enter the number of players [1-4]: ";
    regex reg("[0-9]");
    string condition_str = "an integer at least 1 and at most 4";
    function<bool(int)> conditions = [](int x) {return (x >= 1 && x <= 4);};
    num_players = validate_input(message, reg, condition_str, conditions);
}

// regex matching for acceptable inputs
/*
    print out a prompt message, check that the input is valid, 
    then match the input against the restrictions that define
    all acceptable values
*/
int validate_input(string message, regex desired, string condition_str, function<bool(int)> conditions) {
    string input;
    int num;
    while(true) {
        cout << message;
        cin >> input;

        // making sure you enter something expected
        // (ex. don't want users entering strings when asked for ints)
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

        // only break if both previous checks fail
        // (correct input type) && (passes conditions)
        break;
    };

    // return the number once we know it's safe 
    // to use and within our bounds
    return num;
}

void print_input_error(string input, string condition_str) {
    cout << "\"" << input << "\" is not a valid choice." << endl
         << "You may only enter " << condition_str << ".";
}

void print_game_information() {
    cout << endl << "Class information:" << endl
         << "------------------" << endl;
    for(int i = 0; i < 3; i++) {
        cout << CLASS_TYPES[i] << endl
             << "\t- base health: " << CLASS_BASE_HEALTH[i] << endl
             << "\t- base damage: " << CLASS_BASE_DAMAGE[i] << endl;
    }

    // waits until a player pressey a key
    wait_until_key();

    cout << "Player information:" << endl
         << "----------------------" << endl
         << "Each player starts out with 4 items:" << endl;
    for(int i = 0; i < NUM_ITEMS; i++) {
        cout << "\t -" << ITEMS[i] << ": " << ITEM_DESCRIPTIONS[i] << endl;
    }
    cout << "Once you use an item, you cannot use it again." << endl
         << "To win, defeat the dragon in the castle." << endl
         << "If all party members die, you lose." << endl
         << "Good luck." << endl << endl;
    
    // waits until a player presses a key
    wait_until_key();
}

// prompt each player to input their name and class
void player_choose_info() {
    string message = "";
    regex reg("[0-9]");
    string condition_str = "an integer at least 0 and at most 2";
    function<bool(int)> condition = [](int x) {return (x >= 0 && x <=2);};
    
    // get player names and update `player_names`
    for(int i = 0; i < num_players; i++) {
        string name;
        cout << "Player " << i << ", enter your name (max length 25): ";
        cin >> name;

        // ensuring that each name will be at most
        // 25 characters + 1 null terminator
        char safe_name[26];
        strncpy(safe_name, name.c_str(), 25);
        safe_name[25] = '\0'; // 26th character should be a null terminator

        // update player name with safe type
        strcpy(player_names[i], safe_name);
    }

    print_class_options();
    cout << endl;

    // get player classes and update `player_class`
    for(int i = 0; i < num_players; i++) {
        string name = player_names[i];
        message = name + ", choose a class: ";

        // update the player's information
        int selection = validate_input(message, reg, condition_str, condition);
        player_class[i] = selection;
        player_hp[i] = CLASS_BASE_HEALTH[selection];
        player_damage[i] = CLASS_BASE_DAMAGE[selection];
    }
}

void print_class_options() {
    cout << endl << "Class options: " << endl
         <<     "--------------" << endl;
    for(int i = 0; i < NUM_CLASSES; i++) {
        cout << "\t[" << i << "] " << CLASS_TYPES[i] << endl;
    }
}

#ifdef __APPLE__
#include <cstdlib>
void wait_until_key() {
    cout << "\n\nPress any key to continue...";
    system("read");
}
#else
void wait_until_key() {
    system("pause");
}
#endif

// the primary game loop
/* 
    this function essentially only handles
    moving the party around, since what they can 
    do is entirely dependent on where they are.
    it also checks the win and lose conditions,
    and ends the game if either are met. 
*/
void start_game() {
    game_over = false;
    defeated_dragon = false;

    // party starts at the town
    party_location = 0;
    town();

    // main game loop
    while(true) {

        // go to the party's chosen location
        switch(party_location) { // (party_location chosen at end of each location function)
            case 0: town(); break;
            case 1: mineshaft(); break;
            case 2: castle(); break;
        }

        // check win/lose conditions
        if(game_over) {
            lose_screen();
            return;
        }
        else if (defeated_dragon) {
            win_screen();
            return;
        }
    }
}

// the town
/*
    the location where players start

    this function must:
        - allow the users to leave (you can do this just by
          changinge `party_location` to 1 or 2 and then 
          returning nothing, though make sure to list
          the locations)
*/
void town() {
    cout << "You are in the town. Where do you want to go next?" << endl;
    cout << "1. Mineshaft" << endl;
    cout << "2. Castle" << endl;
    cout << "Enter the number of your choice: \n";
     
    int choice;
    cin >> choice;

    if (choice == 1) {
        party_location = 1; // Go to Mineshaft
    } else if (choice == 2) {
        party_location = 2; // Go to Castle
    } else {
        cout << "Invalid choice. Please choose again." << endl;
        town(); // Recursive call to let the player choose again
    }
}

// the mineshaft
/*
    the location where the players battle random enemies
    (except for the dragon). You may add as many enemies
    as you want, provided you make the proper modifications
    to the parallel arrays above the prototype section under
    enemy data

    this function must:
        - change `game_over` to true if every player
          has died
        - after an encounter, allow the users to leave 
          (you can do this just by changinge `party_location` 
          to 1 or 2 and then returning nothing, though make sure 
          to list the locations)
*/
void mineshaft() {
    /*
        Combat system suggestions:

        Having a separate function that does the entirety of one
        battle would be the best solution (in my opinion), since
        you wouldn't have to rewrite basically everything the exact
        same except for the enemy type (which is the only thing that
        changes between mineshaft battles and the castle battle).

        I would recommend doing all the logic inside a function with
        an appropriate name (something like battle() or battle_simulation()),
        which take in an int corresponding to the type of enemy that
        the party will be fighting.

        Then, use that int to determine the current_hp and current_damage
        (as i've shown below)
        
        The rest should be pretty much the same as here, but having it
        in its own function will make this function (mineshaft()) as well
        as castle() much more readable.

        A simplified version might look like:
        -------------------------------------
        void battle(int enemy_type) { // <- maybe include multiple enemies or number of enemies as well
            current_enemy_hp = enemy_type_base_hp; // <- for multiple enemies you could use an array
            current_enemy_damage = enemy_type_base_damage; // ^
            while(true) {
                player_turn() // <- players can attack enemies, use items (i know evan wanted to
                                                                              do more item stuff)
                enemy_turn() // <- players can only die in an enemy's turn
                
                if(all players dead) {
                    game_over = true;
                    print_defeat_message();
                    return; // <- logic in start_game() will handle stopping the game
                }
                if(all enemies defeated) break;
            }

            // outside loop, enemy defeated
            enemy_defeated_message();
            choose_next_action(); // <- can either battle again or leave
        }



        See the comments I made below for additional concerns.
    */
    battle();
    
    if (current_enemy_hp <= 0) {
        // Allow players to choose where to go next
        cout << "Where do you want to go next?" << endl;
        cout << "1. Return to town" << endl;
        cout << "2. Continue in the mineshaft\n" << endl;
        cout << "Enter the number of your choice: \n";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            party_location = 0; // Go back to Town
        } else {
            mineshaft(); // Continue exploring the Mineshaft
        }
    }
    
}

// the castle
/*
    the location where the party encounters the final boss
    and can defeat it and win the game or all die and lose

    this function must:
        - only allow party once they have defeated at least 
          1 enemy (in the mineshaft)
        - lock the players in once they enter
        - change `game_over` to true if
          the all the players die, then return nothing
        - change `won` to true if 
          the dragon is defeated, then return nothing
*/
void castle() {
    if (!defeated_enemy) {
        cout << "You need to defeat an enemy before entering the castle." << endl;
        party_location = 0;
    } else {
        dragon_battle();
    }
}

// prints that the players have lost (all of them died)
void win_screen() {
 cout << "Congratulations! You have won the game!" << endl;
}
// prints that the players have won
void lose_screen() {
  cout << "Game Over. You have been defeated." << endl;
}

void battle() {
    current_enemy_hp = BASE_ENEMY_HP[MINESHAFT_ENEMIES];
    current_enemy_damage = BASE_ENEMY_DAMAGE[MINESHAFT_ENEMIES];

    int randomIndex = rand() % MINESHAFT_ENEMIES;
    const char* enemyType = ENEMY_TYPES[randomIndex];
    cout << "\nYou encounter a " << enemyType << "\n" << endl;

        while (true) {
            //Player's turn in mineshaft
            for (int i = 0; i < MAX_PLAYERS; i++) {
                if (player_hp[i] > 0) { //Player is alive
                    cout << "Player " << i << ", choose your action:" << endl;
                    cout << "1. Attack\n" << endl;
                    cout << "Enter the number of your choice: \n" << endl;
                    int action;
                    cin >> action;
                    
                    switch (action) {
                        case 1: //Player attacks the enemy
                            current_enemy_hp -= player_damage[MAX_PLAYERS];
                            break;
                        default:
                            cout << "Invlaid Input. Please try again" << endl;
                            i -= 1;
                    }
                }
            }
            //Check if enemy is alive
            if (current_enemy_hp <= 0) {
                cout << "\nEnemy defeated!\n" << endl;
                defeated_enemy = true;
                break;
            } else {
                // If all players are defeated
                if (player_hp[MAX_PLAYERS] <= 0) {
                    game_over = true;
                    return;
                }
            }
            
            //Enemy's turn
            for (int i = 0; i < MAX_PLAYERS; i++) {
                if (player_hp[i] <= 0) {
                    continue;
                }
                // damage line here
                player_hp[i] -= current_enemy_damage;
                cout << "The " << enemyType << " attacks player " << i << " and deals " << current_enemy_damage << " damage." << endl;
                if (player_hp[i] <= 0) {
                    cout << "Player " << i << " has been defeated!" << endl;
                }
            }
        }
}

void dragon_battle() {
    cout << "You enter the castle!" << endl;
    cout << "The doors slam behind you, and you stand face to face with a dragon!\n" << endl;
    
    int dragon_hp = FINAL_BOSS_HP[0];
    int damage = FINAL_BOSS_DAMAGE[0];
    
     while(true) {
        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (player_hp[i] <= 0) {
                continue;
            }
            cout << "Player " << i << ", choose your action:" << endl;
            cout << "1. Attack\n" << endl;
            cout << "Enter the number of your choice: \n" << endl;
            int action;
            cin >> action;
            
            if (action == 1) {
                dragon_hp -= player_damage[i];
                cout << "You deal " << player_damage[i] << " damage to the dragon!" << endl;
            } else {
                cout << "Invalid input. Please Try Again." << endl;
                i -= 1;
            }
            
        }
         
        if (dragon_hp <= 0) {
             cout << "you have defeated the dragon!" << endl;
             defeated_dragon = true;
             return;
         }
         
         //Dragons turn
         for (int i = 0; i < MAX_PLAYERS; i++) {
             if (player_hp[i] <= 0) {
                 continue;
             }
             // damage line here
             player_hp[i] -= damage;
             cout << "The dragon attacks player " << i << " and deals " << damage << " damage." << endl;
             if (player_hp[i] <= 0) {
                 cout << "Player " << i << " has been defeated!" << endl;
             }
         }
         
        for (int i = 0; i < num_players; i++) {
            if (player_hp[MAX_PLAYERS] <= 0) {
                game_over = true;
                return;
        }
    }
}

