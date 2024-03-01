#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

const int MAX_ENEMIES = 3;
const int MAX_ITEMS = 3;
const int MAX_PLAYERS = 3;

// Parallel arrays to store player data
const char* playerNames[MAX_PLAYERS] = {"Warrior", "Mage", "Rogue"};
int playerHP[MAX_PLAYERS] = {20, 15, 10};
int playerDamage[MAX_PLAYERS] = {5, 3, 2};

// Parallel arrays to store enemy data
const char* enemyNames[MAX_ENEMIES] = {"Dragon", "Ogre", "Goblin"};
int enemyHP[MAX_ENEMIES] = {20, 15, 10};
int enemyDamage[MAX_ENEMIES] = {5, 3, 2};

// Parallel arrays to store item data
const char* itemNames[MAX_ITEMS] = {"Potion", "Sword", "Shield"};
const char* itemEffects[MAX_ITEMS] = {"restores 10 HP", "increases damage by 2", "increases defense"};

// Function to display player status
void displayPlayerStatus(int playerIndex) {
    cout << "Player: " << playerNames[playerIndex] << "\n";
    cout << "HP: " << playerHP[playerIndex] << "\n";
}

// Function to simulate a battle encounter
void battleEncounter(int playerIndex) {
    int enemyIndex = rand() % MAX_ENEMIES; // Randomly select enemy

    cout << "You encounter a " << enemyNames[enemyIndex] << "!\n";

    // Simulate battle
    while (playerHP[playerIndex] > 0 && enemyHP[enemyIndex] > 0) {
        // Player's turn
        cout << "Your turn: Choose an action (1. Attack, 2. Use item, 3. Flee): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "You attack the " << enemyNames[enemyIndex] << "!\n";
            enemyHP[enemyIndex] -= playerDamage[playerIndex];
            cout << "Enemy HP: " << enemyHP[enemyIndex] << "\n";
        } else if (choice == 2) {
            cout << "Choose an item to use:\n";
            for (int i = 0; i < MAX_ITEMS; ++i) {
                cout << i+1 << ". " << itemNames[i] << " - " << itemEffects[i] << "\n";
            }
            int itemChoice;
            cin >> itemChoice;
            if (itemChoice >= 1 && itemChoice <= MAX_ITEMS) {
                cout << "You use " << itemNames[itemChoice - 1] << "!\n";
                // Apply item effect (for simplicity, just restore player's HP)
                playerHP[playerIndex] += 10; // Restore 10 HP
                cout << "Your HP: " << playerHP[playerIndex] << "\n";
            } else {
                cout << "Invalid item choice.\n";
            }
        } else if (choice == 3) {
            cout << "You flee from the battle!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }

        // Enemy's turn
        if (enemyHP[enemyIndex] > 0) {
            cout << "The " << enemyNames[enemyIndex] << " attacks you!\n";
            playerHP[playerIndex] -= enemyDamage[enemyIndex];
            cout << "Your HP: " << playerHP[playerIndex] << "\n";
        }
    }

    // Check battle outcome
    if (playerHP[playerIndex] <= 0) {
        cout << "Game over! You were defeated.\n";
    } else if (enemyHP[enemyIndex] <= 0) {
        cout << "You defeated the " << enemyNames[enemyIndex] << "!\n";
    }
}

// Main function
int main() {
    // Seed random number generator
    srand(time(nullptr));

    // Character creation
    char playerName[50];
    cout << "Enter your name: ";
    cin >> playerName;

    cout << "Welcome, " << playerName << "! Choose your class (1. Warrior, 2. Mage, 3. Rogue): ";
    int playerClass;
    cin >> playerClass;

    int playerIndex = playerClass - 1;

    // Display player status
    displayPlayerStatus(playerIndex);

    // Start the game loop
    while (playerHP[playerIndex] > 0) {
        // Simulate battle encounter
        battleEncounter(playerIndex);
    }

    return 0;
}
