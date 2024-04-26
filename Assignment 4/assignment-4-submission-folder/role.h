#ifndef ROLE_H
#define ROLE_H

// this file contains the role enum

enum Role {
    Archer,
    Warrior,
    Mage,

    // this role is only used for items than anyone can use;
    // a player's role cannot be Anyone
    Anyone
};

// returns the base health of a given role
int get_role_health(Role);

#endif