#include "Tower.h"
#include "TileType.h"

Tower::Tower(ElementType elementType): Weapon(elementType) {
    setUp();
}

unsigned int Tower::getFireRate() const {
    return fire_rate;
}

void Tower::attack() {
    if(hasLockOn())
        if(timeof_last_shot.getElapsedTime().asMilliseconds() >= getFireRate()) {
            getLockOn()->takeDamage(getDamage());
            timeof_last_shot.restart();
        }
}

TileType Tower::canBeBuilt() {
    return TileType::typeField;
}

