#include "Trap.h"
#include "TileType.h"

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

TileType Trap::canBeBuilt() {
    return TileType::typePath;
}