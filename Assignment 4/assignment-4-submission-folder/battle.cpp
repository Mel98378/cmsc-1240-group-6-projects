#include "battle.h"
#include "ui.h"
#include "player.h"
#include "item.h"
#include "treasure.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Get enemy based on its type
Enemy* get_enemy_of_type(Enemy_Type enemyType) {
    Enemy* enemy = new Enemy();
    switch (enemyType) {
        case Shrimp:
            enemy->name = "Shrimp";
            enemy->description = "This small agile creature attacks quick and painfully!";
            enemy->damage = 100;
            enemy->health = 5;
            break;
        case Mosquito:
            enemy->name = "Mosquito";
            enemy->description = "This quick, annoying insect has a painful bite!";
            enemy->damage = 10;
            enemy->health = 30;
            break;
        case Mimic:
            enemy->name = "Mimic";
            enemy->description = "This sneaky creature is tricky and deceptive!";
            enemy->damage = 10;
            enemy->health = 40;
            break;
        case Dragon:
            enemy->name = "Dragon";
            enemy->description = "This fearsome beast is garding the castle!";
            enemy->damage = 30;
            enemy->health = 100;
            break;
    }
    return enemy;
}

// Delete an enemy
Enemy* delete_enemy(Enemy* enemy) {
    delete[] enemy->name;
    delete[] enemy->description;
    delete enemy;
    return nullptr;
}

// Battle function
void battle_turn(Player* player, Party* party, Enemy* enemy) {
    string playerMessage = "Player " + string(player->name) + ", choose your action\n1. Attack\n2. Use item\n";
    int action = get_menu_choice(playerMessage.c_str());
    switch (action) {
        case '1': // Attack
            enemy->health -= get_item_effect(Item_Type());
            cout << "Player " << player << " attacks and deals " << Item_Type() << " damage." << endl;
            break;
        case '2': // Use item
            if (player->inv <= 0) {
                cout << "You don't have any items." << endl;
                battle_turn(player, party, enemy);
            } else {
                cout << "Choose your item " << endl;
                string input = get_item_name(Item_Type());
                cin >> input;
                get_item_effect(Item_Type());
                }
            break;
        default:
            cout << "Invalid Input. Please try again." << endl;
            battle_turn(player, party, enemy);
            break;
    }
}

bool enemyDefeated = false;
// Mineshaft battle
void mineshaft_battle(Party* party, Player* players) {
    srand(time(nullptr));
    int randIndex = rand();
    Enemy_Type enemyType;
    switch (randIndex) {
        case 0:
            enemyType = Shrimp;
            break;
        case 1:
            enemyType = Mosquito;
            break;
        case 2:
            enemyType = Mimic;
            break;
    }
    Enemy* enemy = get_enemy_of_type(enemyType);
    cout << "\nYou encounter a " << enemy->name << "\n" << endl;

    // Battle loop
    while (true) {
        // Players turn
        for (int i = 0; i < party->num_players; i++) {
            if (players[i].health <= 0) {
                continue;
            }
            battle_turn(players, party, enemy);
            
            // Check if enemy is defeated
            if (enemy->health <= 0) {
                cout << "\nEnemy Defeated!\n" << endl;
                enemyDefeated = true;
                break;
            }
        }

        // Enemy's turn
        int targetIndex;
        do {
            targetIndex = rand() % party->num_players;
        } while (players[targetIndex].health <= 0);
        // Damage
        players[targetIndex].health -= enemy->damage;
        cout << "The " << enemy->name << " attacks player " << targetIndex << " and deals " << enemy->damage << " damage." << endl;
        // Check if player is alive
        if (players[targetIndex].health <= 0) {
            cout << "Player " << targetIndex << " has been defeated!" << endl;
        }

        //Check if all players are defeated
        bool allPlayersDefeated = true;
        for (int i = 0; i < party->num_players; i++) {
            if (players[i].health > 0) {
                allPlayersDefeated = false;
                break;
            }
        }
        if (allPlayersDefeated) {
            cout << "All players have been defeated!" << endl;
            party->state = Game_State::Lost;
            return;
        }
    }
    delete_enemy(enemy);
}

// Castle Battle
void castle_battle(Party* party, Player* player, Enemy* enemy) {
    // Check if enemy is defeated
    if(!enemyDefeated) {
        cout << "You must defeat an enemy in the mineshaft before you can enter the castle!" << endl;
        return;
    }

    srand(time(nullptr));
    Enemy* dragon = get_enemy_of_type(Dragon);
    cout << "You enter the castle!\n" << endl;
    cout << "The doors slam behind you, and you stand face to face witht he mighty dragon!\n" << endl;

    // Battle loop
    while (true) {
        // Players turn
        for (int i = 0; i < party->num_players; i++) {
            if (player[i].health <= 0) {
                continue;
            }
            battle_turn(player, party, dragon);
            
        // Check if enemy is defeated
            if (enemy->health <= 0) {
                cout << "\nEnemy Defeated!\n" << endl;
                party->state = Game_State::Won;
                return;
            }
        }

        // Dragon's turn
        for (int i = 0; i < party->num_players; i++) {
            if (player[i].health > 0) {
                player[i].health -= dragon->damage;
                cout << "The dragon attacks player " << i << " and deals " << dragon->damage << " damage." << endl;
                if (player[i].health <= 0) {
                    cout << "Player " << i << " has been defeated." << endl;
                }
            }
        }

        //Check if all players are defeated
        bool allPlayersDefeated = true;
        for (int i = 0; i < party->num_players; i++) {
            if (player[i].health > 0) {
                allPlayersDefeated = false;
                break;
            }
        }
        if (allPlayersDefeated) {
            cout << "All players have been defeated!" << endl;
            party->state = Game_State::Lost;
            return;
        }
    }

    // Delete dragon
    delete_enemy(dragon);
}