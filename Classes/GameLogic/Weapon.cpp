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

//bool Tower::isInRange(const Enemy::Ptr &enemy) {
//    // https://stackoverflow.com/a/40259331
//    // also have to take the radius shape hit box thing in consideration..
//    // because, again we didn't work with origins :(
//    const float distance = std::hypot((enemy->getPosition().x - getPosition().x - radius_shape.getPosition().x),
//                                      (enemy->getPosition().y - getPosition().y - radius_shape.getPosition().y));
//
//    return distance <= static_cast<float>(getRange() * TILE_SIZE);
//}

void Weapon::setRange(unsigned int range_var) {
    range = range_var;
}

void Weapon::setDamage(unsigned int damage_var) {
    damage = damage_var;
}