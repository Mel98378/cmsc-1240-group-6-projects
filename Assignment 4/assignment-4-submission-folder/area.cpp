#include "player.h"
#include "ui.h"
#include "area.h"
#include "battle.h"
#include "save.h"
#include <iostream>

void town(Party* party) {
    std::cout << "You are in the town. What do you want to do?" << std::endl;
    std::cout << "1. Go to the mineshaft" << std::endl;
    std::cout << "2. Go to the castle" << std::endl;
    std::cout << "3. Save the game" << std::endl;
    std::cout << "4. Quit the game" << std::endl;
     
    char choice = get_menu_choice("1234");
    std::cout << std::endl;

    switch(choice) {
        case '1': party->location = Area::Mineshaft; break;
        case '2': party->location = Area::Castle; break;
        case '3': save_game(party); break;
        case '4': 
            party->state = Game_State::Quit;
            return;
        default: std::cout << "Invalid choice. Please choose again." << std::endl; town(party); break;
    }
}

void mineshaft(Party* party) {
    while(true) {
        mineshaft_battle(party);
        if(party->state == Game_State::Lost) {return;}
        
        // Allow players to choose what to do next
        std::cout << "Where do you want to do next?" << std::endl;
        std::cout << "1. Return to town" << std::endl;
        std::cout << "2. Continue in the mineshaft without saving" << std::endl;
        std::cout << "3. Save and continue" << std::endl;
        std::cout << "Enter the number of your choice: ";
        
        char choice = get_menu_choice("123");
        std::cout << std::endl;
        switch(choice) {
            case '1': party->location = Area::Town; return;
            case '3': save_game(party); 
            default: break;
        }
    }
}

void castle(Party* party) {
    // allow the players to save
    std::cout << "Do you want to save before challenging the dragon? [y/n]: ";
    char choice = get_menu_choice("yn");
    std::cout << std::endl;
    if(choice == 'y') {
        save_game(party);
    }

    castle_battle(party);
}