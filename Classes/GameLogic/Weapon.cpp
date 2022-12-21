#include "Weapon.h"
#include "../GUI/Level.h"

#include <cmath>
#include <utility>

Weapon::Weapon(ElementType elementType) : type(elementType) {
}

unsigned int Weapon::getRange() const {
    return range;
}

unsigned int Weapon::getDamage() const {
    return damage;
}

ElementType Weapon::getElementType() const {
    return type;
}

void Weapon::lockOn(std::weak_ptr<Enemy> enemy) {
    curr_focussed_enemy = std::move(enemy);
}

bool Weapon::hasLockOn() {
    return !curr_focussed_enemy.expired();
}

void Weapon::validateLockOn() {
    if (!hasLockOn() || !isInRange(getLockOn()))
        curr_focussed_enemy.reset();
}

Enemy::Ptr Weapon::getLockOn() {
    return curr_focussed_enemy.lock();
}

bool Weapon::isInRange(const Enemy::Ptr &enemy) {

}

void Weapon::setRange(unsigned int range_var) {
    range = range_var;
}

void Weapon::setDamage(unsigned int damage_var) {
    damage = damage_var;
}