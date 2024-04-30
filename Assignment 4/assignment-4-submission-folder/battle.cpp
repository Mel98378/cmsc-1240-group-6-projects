#include "battle.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// Enemy Struct
struct Enemy {
    const char* name;
    const char* description;
    int damage;
    int health;
};

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
            enemy->description = "...";
            enemy->damage = 10;
            enemy->health = 30;
            break;
        case Mimic:
            enemy->name = "Mimic";
            enemy->description = "...";
            enemy->damage = 10;
            enemy->health = 40;
            break;
        case Dragon:
            enemy->name = "Dragon";
            enemy->description = "...";
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
void battle_turn(int playerIndex, Party* party, Enemy* enemy) {
    cout << "Player " << playerIndex << ", choose your action: " << endl;
    cout << "1. Attack" << endl;
    cout << "2. Use an Item" << endl;
    int action;
    switch (action) {
        case 1: // Attack
            enemy->health -= party->players[playerIndex].damage;
            cout << "Player " << playerIndex << " attacks and deals " << party->players[playerIndex].damage << " damage." << endl;
            break;
        case 2: // Use item
            if (!player_has_items(&party->players[playerIndex])) {
                cout << "You don't have any items." << endl;
                battle_turn(playerIndex, part, enemy);
            } else {
                use_item(&party->players[playerIndex]);
            }
            break;
        default:
            cout << "Invalid Input. Please try again." << endl;
            battle_turn(playerIndex, party, enemy);
            break;
    }
}

bool enemyDefeated = false;
// Mineshaft battle
void mineshaft_battle(Party* party) {
    srand(time(nullptr));
    int randIndex = rand() % MINESHAFT_ENEMIES;
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
            if (party->players[i].health <= 0) {
                continue;
            }
            battle_turn(i, party, enemy);

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
        } while (party->players[targetIndex].health <= 0);
        // Damage
        party->players[targetIndex].health -= enemy->damage;
        cout << "The " << enemy->name << " attacks player " << targetIndex << " and deals " << enemy->damage << " damage." << endl;
        // Check if player is alive
        if (party->players[targetIndex].health <= 0) {
            cout << "Player " << targetIndex << " has been defeated!" << endl;
        }

        //Check if all players are defeated
        bool allPlayersDefeated = true;
        for (int i = 0; i < party->num_players; i++) {
            if (party->players[i].health > 0) {
                allPlayersDefeated = false;
                break;
            }
        }
        if (allPlayersDefeated) {
            cout << "All players have been defeated!" << endl;
            break;
        }
    }
    delete_enemy(enemy);
}

// Castle Battle
void castle_battle(Party* party) {
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
            if (party->players[i].health <= 0) {
                continue;
            }
            battle_turn(i, party, enemy);
            
        // Check if enemy is defeated
            if (enemy->health <= 0) {
                cout << "\nEnemy Defeated!\n" << endl;
                break;
            }
        }

        // Dragon's turn
        for (int i = 0; i < party->num_players; i++) {
            if (party->players[i].health > 0) {
                party->players[i].health -= Dragon->damage;
                cout << "The dragon attacks player " << i << " and deals " << dragon->damage << " damage." << endl;
                if (party->players[i].health <= 0) {
                    cout << "Player " << i << " has been defeated." << endl;
                }
            }
        }

        //Check if all players are defeated
        bool allPlayersDefeated = true;
        for (int i = 0; i < party->num_players; i++) {
            if (party->players[i].health > 0) {
                allPlayersDefeated = false;
                break;
            }
        }
        if (allPlayersDefeated) {
            cout << "All players have been defeated!" << endl;
            break;
        }
    }

    // Delete dragon
    delete_enemy(Dragon);
}