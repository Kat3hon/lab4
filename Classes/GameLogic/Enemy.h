#pragma once
#define HEALTH_BAR_LENGTH 35
#define HEALTH_BAR_HEIGHT 2

#include "../GUI/GameObject.h"

#include <memory>
#include <functional>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <SFML/System/Vector2.hpp>

class Enemy : public GameObject, public std::enable_shared_from_this<Enemy> {

    /// Sprite of the enemy. Texture being provided by parent class
    sf::Sprite sprite;

    /// Healthbars
    sf::RectangleShape back_ground_healthbar;
    sf::RectangleShape fore_ground_healthbar;

    /// Health of enemy
    unsigned int health;

    // As the name implies.
    // The amount of health the enemy used to have
    unsigned m_initialHealth;

    // Progress of the enemy in the map. Could be anything.
    // Higher the progress, more chance of being focused by a tower.
    unsigned int m_progress;

    // The current path this enemy is on.
    unsigned int m_pathingIndex;

    // The amount of X this enemy has to move each update
    float m_moveX;

    // The amount of Y this enemy has to move each update
    float m_moveY;

    // The amount of distance the enemy needs to cover
    // until it needs to request a new path.
    float m_distance;

    unsigned int m_goldWorth;

    // callback when enemy reaches end of path
   // EnemyGoalHandler m_goalHandler;

    // callback when enemy gets killed by tower
    //EnemyDeadHandler m_enemyDeadHandler;

public:
    using Ptr = std::shared_ptr<Enemy>;
    using EnemyGoalHandler = std::function<void(const Enemy::Ptr&)>;
    using EnemyDeadHandler = std::function<void(const Enemy::Ptr&)>;

    explicit Enemy(unsigned int health, unsigned int goldWorth = 10, bool isBoss = false);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const; //override

    void setGoalHandler(EnemyGoalHandler handler);

    void setEnemyDeadHandler(EnemyDeadHandler handler);

    void kill();

    void step();

    void reachGoal();

    //void setDirection(Direction direction, sf::Vector2<float> targetPosition);

    void setTexture(const sf::Texture &texture, const sf::Rect<int> &texCoords);

    bool needsNewPath() const;

    void takeDamage(unsigned int damage);

    unsigned int getGoldWorth();

    unsigned int getProgress();

    unsigned int getHealth() const;

    unsigned int getPathingIndex();
};

