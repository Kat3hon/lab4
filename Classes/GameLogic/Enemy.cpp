#include "Enemy.h"
#include <cmath>
#include <utility>

Enemy::Enemy(unsigned int health, unsigned int goldWorth, bool isBoss)
        : GameObject(), health(health), m_goldWorth(goldWorth), m_isBoss(isBoss), m_progress(0),
          m_pathingIndex(0),
          m_moveX(0.f), m_moveY(0.f), m_distance(0.f) {
    m_initialHealth = health;

    fore_ground_healthbar.setFillColor(sf::Color::Green);
    back_ground_healthbar.setFillColor(sf::Color::Red);

    fore_ground_healthbar.setSize({HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT});
    back_ground_healthbar.setSize({HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT});

    fore_ground_healthbar.setPosition(-HEALTH_BAR_LENGTH / 2.f, -20.f);
    back_ground_healthbar.setPosition(-HEALTH_BAR_LENGTH / 2.f, -20.f);
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(sprite, states);

    if (m_initialHealth > health) {
        target.draw(back_ground_healthbar, states);
        target.draw(fore_ground_healthbar, states);
    }
}

void Enemy::takeDamage(unsigned int damage) {
    if (damage >= health) {
        health = 0;
        return kill();
    }

    health -= damage;

    const float healthPercentage = 100.f / static_cast<float>(m_initialHealth) * static_cast<float>(health);
    fore_ground_healthbar.setSize(
            {HEALTH_BAR_LENGTH / 100.f * healthPercentage, HEALTH_BAR_HEIGHT});
}

unsigned int Enemy::getHealth() const {
    return health;
}

unsigned int Enemy::getProgress() {
    return m_progress;
}

void Enemy::setTexture(const sf::Texture &texture, const sf::Rect<int> &texCoords) {
    sprite.setTexture(texture);
    sprite.setTextureRect(texCoords);

    // Set the origin to the center of the sprite
    // Since that's more convenient for us.
    sprite.setOrigin(texCoords.width / 2.f, texCoords.height / 2.f);
}

void Enemy::step() {
    if (m_distance <= 0) {
        return;
    }

    // maybe this is in the wrong place
    // the purpose of this is to only let the enemy move a certain distance
    // this distance is predefined by 'something else'
    if (m_distance >= std::abs(m_moveY + m_moveX)) {
        m_distance -= std::abs(m_moveY + m_moveX);
    } else m_distance = 0;

    move(m_moveX, m_moveY);
}

unsigned int Enemy::getPathingIndex() {
    return m_pathingIndex;
}

void Enemy::setDirection(Direction direction, sf::Vector2<float> targetPosition) {
    m_pathingIndex++;

    float leftOverX = targetPosition.x - getPosition().x;
    float leftOverY = targetPosition.y - getPosition().y;

    m_distance = std::abs(leftOverX + leftOverY);

    if (direction == Direction::North) {
        m_moveX = 0.f;
        m_moveY = -1.f;

        sprite.setRotation(180);

        return;
    }

    if (direction == Direction::East) {
        m_moveX = 1.f;
        m_moveY = 0.f;

        sprite.setRotation(270);

        return;
    }

    if (direction == Direction::South) {
        m_moveX = 0.f;
        m_moveY = 1.f;

        sprite.setRotation(0);

        return;
    }

    if (direction == Direction::West) {
        m_moveX = -1.f;
        m_moveY = 0.f;

        sprite.setRotation(90);

        return;
    }
}

bool Enemy::needsNewPath() const {
    return m_distance <= 0.f;
}

void Enemy::setGoalHandler(Enemy::EnemyGoalHandler handler) {
    m_goalHandler = std::move(handler);
}

void Enemy::reachGoal() {
    m_goalHandler(shared_from_this());
}

void Enemy::setEnemyDeadHandler(Enemy::EnemyDeadHandler handler) {
    m_enemyDeadHandler = std::move(handler);
}

void Enemy::kill() {
    m_enemyDeadHandler(shared_from_this());
}

unsigned int Enemy::getGoldWorth() {
    return m_goldWorth;
}