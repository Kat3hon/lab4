#include "Tower.h"
#include "../grid.hpp"

#include <cmath>
#include <utility>

Tower::Tower(TowerType towerType) : type(towerType), range(2), damage(5), fire_rate(500), selected(false), is_built(false) {
    radius_shape.setFillColor(sf::Color{235, 79, 52, 128});
}

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    if (selected || !is_built)
        target.draw(radius_shape, states);

    target.draw(sprite, states);
}

unsigned int Tower::getRange() const {
    return range;
}

unsigned int Tower::getFireRate() const {
    return fire_rate;
}

unsigned int Tower::getDamage() const {
    return damage;
}

void Tower::setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords) {
    sprite.setTexture(texture);
    sprite.setTextureRect(textureCoords);
}

TowerType Tower::getTowerType() const {
    return type;
}

void Tower::lockOn(std::weak_ptr<Enemy> enemy) {
    curr_focussed_enemy = std::move(enemy);
}

void Tower::setSelected(bool selected_var) {
    selected = selected_var;

    radius_shape.setPosition(TILE_SIZE / 2.f, TILE_SIZE / 2.f + 75 - TILE_SIZE);
    radius_shape.setRadius(static_cast<float>(range * TILE_SIZE));
    radius_shape.setOrigin(radius_shape.getRadius(), radius_shape.getRadius());
}

bool Tower::hasLockOn() {
    return !curr_focussed_enemy.expired();
}

void Tower::validateLockOn() {
    if (!hasLockOn() || !isInRange(getLockOn()))
        curr_focussed_enemy.reset();
}

Enemy::Ptr Tower::getLockOn() {
    return curr_focussed_enemy.lock();
}

bool Tower::isInRange(const Enemy::Ptr &enemy) {
    // https://stackoverflow.com/a/40259331
    // also have to take the radius shape hit box thing in consideration..
    // because, again we didn't work with origins :(
    const float distance = std::hypot((enemy->getPosition().x - getPosition().x - radius_shape.getPosition().x),
                                      (enemy->getPosition().y - getPosition().y - radius_shape.getPosition().y));

    return distance <= static_cast<float>(getRange() * TILE_SIZE);
}

void Tower::shoot() {
    if(hasLockOn()) {
        if(timeof_last_shot.getElapsedTime().asMilliseconds() >= getFireRate()) {
            getLockOn()->takeDamage(getDamage());
            timeof_last_shot.restart();
        }
    }
}

void Tower::build() {
    is_built = true;
}

bool Tower::isBuilt() const {
    return is_built;
}