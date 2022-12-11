#include "Tower.h"
#include "../grid.hpp"

#include <cmath>
#include <utility>

Tower::Tower(TowerType towerType) : m_type(towerType), m_range(2), m_damage(5), m_fireRate(500), m_selected(false), m_isBuilt(false) {
    m_radiusShape.setFillColor(sf::Color{235, 79, 52, 128});
}

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    if (m_selected || !m_isBuilt) {
        target.draw(m_radiusShape, states);
    }

    target.draw(m_sprite, states);
}

unsigned int Tower::getRange() {
    return m_range;
}

unsigned int Tower::getFireRate() {
    return m_fireRate;
}

unsigned int Tower::getDamage() {
    return m_damage;
}

void Tower::setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords) {
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(textureCoords);
}

TowerType Tower::getTowerType() {
    return m_type;
}

void Tower::lockOn(std::weak_ptr<Enemy> enemy) {
    m_focussedEnemy = std::move(enemy);
}

void Tower::setSelected(bool selected) {
    m_selected = selected;

    m_radiusShape.setPosition(TILE_SIZE / 2.f, TILE_SIZE / 2.f + 75 - TILE_SIZE);
    m_radiusShape.setRadius(static_cast<float>(m_range * TILE_SIZE));
    m_radiusShape.setOrigin(m_radiusShape.getRadius(), m_radiusShape.getRadius());
}

bool Tower::hasLockOn() {
    return !m_focussedEnemy.expired();
}

void Tower::validateLockOn() {
    // this function will be used
    // to check if the enemy is still in range
    // of this towers radius.
    // if not, deselect the current focused enemy.

    if (!hasLockOn() || !isInRange(getLockOn())) {
        m_focussedEnemy.reset();
    }
}

Enemy::Ptr Tower::getLockOn() {
    return m_focussedEnemy.lock();
}

bool Tower::isInRange(const Enemy::Ptr &enemy) {
    // https://stackoverflow.com/a/40259331
    // also have to take the radius shape hit box thing in consideration..
    // because, again we didn't work with origins :(
    const float distance = std::hypot((enemy->getPosition().x - getPosition().x - m_radiusShape.getPosition().x),
                                      (enemy->getPosition().y - getPosition().y - m_radiusShape.getPosition().y));

    return distance <= static_cast<float>(getRange() * TILE_SIZE);
}

void Tower::shoot() {
    if(hasLockOn()) {
        if(m_lastShot.getElapsedTime().asMilliseconds() >= getFireRate()) {
            getLockOn()->takeDamage(getDamage());
            m_lastShot.restart();
        }
    }
}

void Tower::build() {
    m_isBuilt = true;
}

bool Tower::isBuilt() {
    return m_isBuilt;
}