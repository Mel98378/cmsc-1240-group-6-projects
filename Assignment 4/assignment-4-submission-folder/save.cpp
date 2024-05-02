#include "save.h"
#include "player.h"
#include "area.h"
#include "item.h"
#include <cstdio>
#include <cstdlib>
#include <string>

// local prototype functions
char* inv_as_str(Inventory* inv);
Inventory* inv_from_str(char* string);
char* trim_string_front(char string, int num);

// reconstruct the party from the info in the save file
//MARK: get_save_data()
Party* get_save_data() {

    // open the save file in read (fails if none exists)
    FILE* file = fopen("savedata.txt", "r");

    // check if there is a save
    if(file == nullptr) {
        puts("No save file exists.");
        return create_characters();
    }

    // recreate the party
    Party* party = (Party*) malloc(sizeof(Party));

    // check the area and location data
    int location;
    int enemies_defeated;

    // read the location data
    fseek(file, 9, SEEK_SET);
    location = fgetc(file) - '0';
    fseek(file, 21, SEEK_SET);
    fscanf(file, " %d", &enemies_defeated);

    party->location = (Area)location;
    party->num_enemies = enemies_defeated;
    party->state = Game_State::Playing;

    // get to the start of the new line
    fseek(file, 3, SEEK_CUR);

    // read the player data
    for(int x = 0; x < 4; x++) {
        Player* p = (Player*) malloc(sizeof(Player));
        p->name = (char*) malloc(16);
        p->inv = (Inventory*) malloc(sizeof(Inventory));

        // initialized values
        char line[200] = {0};
        char* name = (char*) malloc(16);
        char* inv = (char*) malloc(50);
        char role = 0;
        char* health = (char*) malloc(4);

        // get the line to parse into the data
        fgets(line, sizeof(line), file); 

        int i = 1;
        
        // get to the start of the player name
        while(line[i - 1] != ':') {
            i++;
        }

        // get the name
        int j = 0;
        while(line[i] != ' ') {
            
            // make sure that we don't try to access more memory than the name allows
            if(j > 14) {
                break;
            }

            // otherwise add the character to the name
            name[j] = line[i];
            i++;
            j++;
        }
        name[j] = '\0';

        // set p0 to nullptr and return early if they have no name
        if(name[0] == '\0') {
            free(name);
            free(inv);
            free(health);
            free(p);
            p = nullptr;
            party->players[x] = p;
            continue;
        }

        // get to the start of the player inventory
        while(line[i - 1] != ':') {
            i++;
        }

        // get the player inventory
        j = 0;
        while(line[i] != ' ') {
            if(j > 49) {
                break;
            }
            inv[j] = line[i];
            i++;
            j++;
        }
        inv[j] = '\0';

        // reach the player role
        while(line[i - 1] != ':') {
            i++;
        }

        // get the player role
        role = line[i];
        i++;

        // reach the player health
        while(line[i - 1] != ':') {
            i++;
        }

        // get the player health
        j = 0;
        while(line[i] != ' ') {
            if(j > 3) {
                break;
            }
            health[j] = line[i];
            i++;
            j++;
        }
        health[j] = '\0';

        // initialize the new player's values
        p->name = name;
        p->inv = inv_from_str(inv);
        free(inv);
        p->role = (Role)(role - '0');
        p->health = std::stoi(health);
        free(health);

        // add the new player to the party
        party->players[x] = p;
    }

    return party;
}

// makes or overwrites a save file
//MARK: save_game()
void save_game(Party* party) {

    // make sure the party exists
    if(party == nullptr) {
        puts("cannot save party that does not exist.");
        return;
    }

    // open the save file, or create it if it doesn't exist
    FILE* file = fopen("savedata.txt", "w");

    // make sure the file opens properly
    if(file == nullptr) {
        perror("unable to open file");
        return;
    }

    // print the party information to the save file
    fprintf(file, "location=%d \n", party->location);
    fprintf(file, "enemies=%d \n", party->num_enemies);

    for(int i = 0; i < 4; i++) {
        Player* p = party->players[i];
        char* name = (char*) malloc(16);
        char* inv = (char*) malloc(50);
        int role;
        int health;

        if(p == nullptr) {
            name[0] = '\0';
            inv[0] = '\0';
            role = 0;
            health = 0;
            fprintf(file, "p%d=name:%s inv:%s role:%d health:%d \n", i, name, inv, role, health);
            continue;
        }

        name = p->name;
        inv = inv_as_str(p->inv);
        role = (int) p->role;
        health = p->health;

        fprintf(file, "p%d=name:%s inv:%s role:%d health:%d \n", i, name, inv, role, health);

        free(inv);
    }

    fclose(file);
}

// converts a player's inventory into a printable string
//MARK: inv_as_str()
char* inv_as_str(Inventory* inv) {
    Inventory* curr = inv;
    char* result = nullptr;

    int i = 0;
    while(curr != nullptr) {
        result = (char*) realloc(result, sizeof(result) + 1);
        result[i] = curr->item + '0';
        curr = curr->next;
        i++;
    }
    if(result == nullptr) {
        return (char*)'\0';
    }
    result[i] = '\0';

    return result;
}

// turns the inventory string from the save file into an inventory
//MARK: inv_from_str()
Inventory* inv_from_str(char* string) {
    Inventory* inv = (Inventory*) malloc(sizeof(Inventory));
    Inventory* head = inv;

    int i = 0;
    while(true) {
        inv->item = (Item_Type) (string[i] - '0');
        if(string[i+1] == '\0') {
            inv->next = nullptr;
            break;
        }
        inv->next = (Inventory*) malloc(sizeof(Inventory));
        inv = inv->next;
        i++;
    }

    return head;
}