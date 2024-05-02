#include "item.h"
#include "role.h"

char* get_item_name(Item_Type item) {
    switch(item) {
        case Item_Type::Bow: return (char*)"Bow";
        case Item_Type::Sword: return (char*)"Sword";
        case Item_Type::Staff: return (char*)"Staff";
        case Item_Type::Health_Potion: return (char*)"Health potion";
        case Item_Type::Vitamin: return (char*)"Vitamin gummy";
        case Item_Type::Rock: return (char*)"Rock";
        case Item_Type::Big_Rock: return (char*)"Big rock";
        default: return (char*)"invalid item";
    }
}

char* get_item_desc(Item_Type item) {
    switch(item) {
        case Item_Type::Bow: return (char*)"Shoots arrows.";
        case Item_Type::Sword: return (char*)"Slashes.";
        case Item_Type::Staff: return (char*)"Casts spells.";
        case Item_Type::Health_Potion: return (char*)"Heals hitpoints.";
        case Item_Type::Vitamin: return (char*)"Increases damage.";
        case Item_Type::Rock: return (char*)"Causes damage.";
        case Item_Type::Big_Rock: return (char*)"Causes a lot of damage.";
        default: return (char*)"an item that doesn't exist.";
    }
}

int get_item_effect(Item_Type item) {
    switch(item) {
        case Item_Type::Bow: return 30;
        case Item_Type::Sword: return 30;
        case Item_Type::Staff: return 40;
        case Item_Type::Health_Potion: return 50;
        case Item_Type::Vitamin: return 30;
        case Item_Type::Rock: return 30;
        case Item_Type::Big_Rock: return 60;
        default: return 0;
    }
}

Role get_item_user(Item_Type item) {
    switch(item) {
        case Item_Type::Bow: return Role::Archer;
        case Item_Type::Sword: return Role::Warrior;
        case Item_Type::Staff: return Role::Mage;
        case Item_Type::Health_Potion: return Role::Anyone;
        case Item_Type::Vitamin: return Role::Anyone;
        case Item_Type::Rock: return Role::Anyone;
        case Item_Type::Big_Rock: return Role::Anyone;
        default: return Role::Anyone;
    }
}