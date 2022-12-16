//
// Created by kklim on 17.12.2022.
//

#include "Trap.h"

Trap::Trap(ElementType elementType):Weapon(elementType) {
    setDamage(50);
    setRange(1);
}

void Trap::attack() {
    if(hasLockOn())
        getLockOn()->takeDamage(getDamage());
    //delete trap from a map?
    setRange(-1);
}