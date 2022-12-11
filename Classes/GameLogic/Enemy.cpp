#include "Enemy.h"
#include <cmath>
#include <utility>

Enemy::Enemy(unsigned int health, EnemyType type, unsigned int goldWorth, bool isBoss)
        : GameObject(), m_type(type), m_health(health), m_goldWorth(goldWorth), m_isBoss(isBoss), m_progress(0),
          m_pathingIndex(0),
          m_moveX(0.f), m_moveY(0.f), m_distance(0.f) {
    m_initialHealth = health;

    m_foreGroundHealthbar.setFillColor(sf::Color::Green);
    m_backGroundHealthbar.setFillColor(sf::Color::Red);

    m_foreGroundHealthbar.setSize({HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT});
    m_backGroundHealthbar.setSize({HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT});

    m_foreGroundHealthbar.setPosition(-HEALTH_BAR_LENGTH / 2.f, -20.f);
    m_backGroundHealthbar.setPosition(-HEALTH_BAR_LENGTH / 2.f, -20.f);
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(m_sprite, states);

    if (m_initialHealth > m_health) {
        target.draw(m_backGroundHealthbar, states);
        target.draw(m_foreGroundHealthbar, states);
    }
}

void Enemy::takeDamage(unsigned int damage) {
    if (damage >= m_health) {
        m_health = 0;
        return kill();
    }

    m_health -= damage;

    const float healthPercentage = 100.f / static_cast<float>(m_initialHealth) * static_cast<float>(m_health);
    m_foreGroundHealthbar.setSize(
            {HEALTH_BAR_LENGTH / 100.f * healthPercentage, HEALTH_BAR_HEIGHT});
}

unsigned int Enemy::getHealth() {
    return m_health;
}

bool Enemy::isAir() {
    return m_type == EnemyType::AirEnemy;
}

bool Enemy::isGrounded() {
    return m_type == EnemyType::GroundEnemy;
}

bool Enemy::isBoss() {
    return m_isBoss;
}

unsigned int Enemy::getProgress() {
    return m_progress;
}

void Enemy::setTexture(const sf::Texture &texture, const sf::Rect<int> &texCoords) {
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(texCoords);

    // Set the origin to the center of the sprite
    // Since that's more convenient for us.
    m_sprite.setOrigin(texCoords.width / 2.f, texCoords.height / 2.f);
}

EnemyType Enemy::getType() {
    return m_type;
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

        m_sprite.setRotation(180);

        return;
    }

    if (direction == Direction::East) {
        m_moveX = 1.f;
        m_moveY = 0.f;

        m_sprite.setRotation(270);

        return;
    }

    if (direction == Direction::South) {
        m_moveX = 0.f;
        m_moveY = 1.f;

        m_sprite.setRotation(0);

        return;
    }

    if (direction == Direction::West) {
        m_moveX = -1.f;
        m_moveY = 0.f;

        m_sprite.setRotation(90);

        return;
    }
}

bool Enemy::needsNewPath() {
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