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

public:
    using Ptr = std::shared_ptr<Enemy>;
    using EnemyGoalHandler = std::function<void(const Enemy::Ptr&)>;
    using EnemyDeadHandler = std::function<void(const Enemy::Ptr&)>;

private:

//    /// Sprite of the enemy. Texture being provided by parent class
//    sf::Sprite sprite;
//
//    /// Healthbars
//    sf::RectangleShape back_ground_healthbar;
//    sf::RectangleShape fore_ground_healthbar;

    /// Health of enemy
    unsigned int health;

    // As the name implies.
    // The amount of health the enemy used to have
    unsigned initial_health;

    // Progress of the enemy in the map. Could be anything.
    // Higher the progress, more chance of being focused by a tower.
    unsigned int progress_value;

    // The current path this enemy is on.
    unsigned int pathing_index;

    unsigned int gold_worth;

    /// Callback when enemy reaches end of path
    EnemyGoalHandler goal_handler;

    /// Callback when enemy gets killed by a weapon
    EnemyDeadHandler enemy_dead_handler;

public:

    explicit Enemy(unsigned int health, unsigned int goldWorth = 10, bool isBoss = false);

    //void draw(sf::RenderTarget &target, sf::RenderStates states) const; //override

    void setGoalHandler(EnemyGoalHandler handler);

    void setEnemyDeadHandler(EnemyDeadHandler handler);

    void kill();

    void step();

    void reachGoal();

    //void setTexture(const sf::Texture &texture, const sf::Rect<int> &texCoords);

    //bool needsNewPath() const;

    void takeDamage(unsigned int damage);

    unsigned int getGoldWorth() const;

    unsigned int getProgress();

    unsigned int getHealth() const;

    unsigned int getPathingIndex() const;
};

