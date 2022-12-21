#include "Castle.h"

void Castle::addHealth(unsigned int health_var) {
    health += health_var;
}

void Castle::substractHealth(unsigned int health_var) {
    if (health_var > health) {
        health = 0;
        return;
    }

    health -= health;
}

void Castle::setHealth(unsigned int health_var) {
    health = health_var;
}

unsigned int Castle::getHealth() const {
    return health;
}