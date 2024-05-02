#include "role.h"

int get_role_health(Role role) {
    switch(role) {
        case Role::Archer: return 60;
        case Role::Warrior: return 70;
        case Role::Mage: return 80;
        default: return 0;
    }
}