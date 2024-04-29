#include "game.h"
#include "save.h"
#include "ui.h"
#include "area.h"

#include <cstdlib>
#include <cstdio>

// local file prototypes
void game_loop(Party*);
void print_lose_screen();
void print_win_screen();

void start_game() {

    // check if the players want to load from a save
    printf("Do you want to load from a save? [y/n]: ");
    char choice = get_menu_choice("yn");
    puts("");

    Party* party = nullptr;

    switch(choice) {
        case 'y': party = get_save_data();
        case 'n': party = create_characters();
    }

    game_loop(party);
}

void game_loop(Party* party) {
    while(party->state = Game_State::Playing) {
        switch(party->location) {
            case Area::Town: town(party); break;
            case Area::Mineshaft: mineshaft(party); break;
            case Area::Castle: castle(party); break;
            default: puts("Invalid area function.");
        }
    }

    if(party->state == Game_State::Lost) {
        print_lose_screen();
    }
    else if(party->state == Game_State::Won) {
        print_win_screen();
    }
}

void print_lose_screen() {
    puts("You won!");
}

void print_win_screen() {
    puts("You lost.");
}