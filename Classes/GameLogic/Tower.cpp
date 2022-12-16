#include "Tower.h"

Tower::Tower(ElementType elementType): Weapon(elementType){
    setRange(2);
    setDamage(5);
    fire_rate = 500;
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