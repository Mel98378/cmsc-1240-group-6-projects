#include "treasure.h"
#include <random>
#include <ctime>

Item_Type treasure() {
    srand(time(nullptr));

    // num can be 3-6 inclusive to match Item_Type enum
    int num = rand() % 4 + 3;

    return (Item_Type)num;
}