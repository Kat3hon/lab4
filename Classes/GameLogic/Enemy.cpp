#include "Enemy.h"
#include <cmath>
#include <utility>

Enemy::Enemy(unsigned int health, unsigned int goldWorth, bool isBoss)
        : GameObject(), health(health), gold_worth(goldWorth), progress_value(0),
          pathing_index(0) {
    initial_health = health;

//    fore_ground_healthbar.setFillColor(sf::Color::Green);
//    back_ground_healthbar.setFillColor(sf::Color::Red);
//
//    fore_ground_healthbar.setSize({HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT});
//    back_ground_healthbar.setSize({HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT});
//
//    fore_ground_healthbar.setPosition(-HEALTH_BAR_LENGTH / 2.f, -20.f);
//    back_ground_healthbar.setPosition(-HEALTH_BAR_LENGTH / 2.f, -20.f);
}

//void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//    //states.transform *= getTransform();
//
//    target.draw(sprite, states);
//
//    if (initial_health > health) {
//        target.draw(back_ground_healthbar, states);
//        target.draw(fore_ground_healthbar, states);
//    }
//}

void Enemy::takeDamage(unsigned int damage) {
    if (damage >= health) {
        health = 0;
        return kill();
    }

    health -= damage;

    const float healthPercentage = 100.f / static_cast<float>(initial_health) * static_cast<float>(health);
//    fore_ground_healthbar.setSize(
//            {HEALTH_BAR_LENGTH / 100.f * healthPercentage, HEALTH_BAR_HEIGHT});
}

unsigned int Enemy::getHealth() const {
    return health;
}

unsigned int Enemy::getProgress() const {
    return progress_value;
}

//void Enemy::setTexture(const sf::Texture &texture, const sf::Rect<int> &texCoords) {
//    sprite.setTexture(texture);
//    sprite.setTextureRect(texCoords);
//
//    // Set the origin to the center of the sprite
//    // Since that's more convenient for us.
//    sprite.setOrigin(texCoords.width / 2.f, texCoords.height / 2.f);
//}

void Enemy::step() {

}

unsigned int Enemy::getPathingIndex() const {
    return pathing_index;
}

void Enemy::setGoalHandler(Enemy::EnemyGoalHandler handler) {
    goal_handler = std::move(handler);
}

void Enemy::reachGoal() {
    goal_handler(shared_from_this());
}

void Enemy::setEnemyDeadHandler(Enemy::EnemyDeadHandler handler) {
    enemy_dead_handler = std::move(handler);
}

void Enemy::kill() {
    enemy_dead_handler(shared_from_this());
}

unsigned int Enemy::getGoldWorth() const {
    return gold_worth;
}