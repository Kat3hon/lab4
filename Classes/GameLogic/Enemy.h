#define HEALTH_BAR_LENGTH 35
#define HEALTH_BAR_HEIGHT 2

#include "GameObject.h"
#include "EnemyType.h"
#include "../direction.hpp"

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

    explicit Enemy(unsigned int health, EnemyType type = EnemyType::GroundEnemy, unsigned int goldWorth = 10, bool isBoss = false);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setGoalHandler(EnemyGoalHandler handler);

    void setEnemyDeadHandler(EnemyDeadHandler handler);

    void kill();

    void step();

    void reachGoal();

    void setDirection(Direction direction, sf::Vector2<float> targetPosition);

    void setTexture(const sf::Texture &texture, const sf::Rect<int> &texCoords);

    bool needsNewPath();

    void takeDamage(unsigned int damage);

    unsigned int getGoldWorth();

    bool isGrounded();

    bool isAir();

    bool isBoss();

    unsigned int getProgress();

    unsigned int getHealth();

    unsigned int getPathingIndex();

    EnemyType getType();

private:
    // Type of the enemy. This is not a race
    EnemyType m_type;

    // Sprite of the enemy. Texture being provided by parent class
    sf::Sprite m_sprite;

    sf::RectangleShape m_backGroundHealthbar;
    sf::RectangleShape m_foreGroundHealthbar;

    // Health of enemy
    unsigned int m_health;

    // As the name implies.
    // The amount of health the enemy used to have
    unsigned m_initialHealth;

    // Progress of the enemy in the map. Could be anything.
    // Higher the progress, more chance of being focused by a tower.
    unsigned int m_progress;

    // The current path this enemy is on.
    unsigned int m_pathingIndex;

    // If this enemy is a boss or not
    bool m_isBoss;

    // The amount of X this enemy has to move each tick
    float m_moveX;

    // The amount of Y this enemy has to move each tick
    float m_moveY;

    // The amount of distance the enemy needs to cover
    // until it needs to request a new path.
    float m_distance;

    unsigned int m_goldWorth;

    // callback when enemy reaches end of path
    EnemyGoalHandler m_goalHandler;

    // callback when enemy gets killed by tower
    EnemyDeadHandler m_enemyDeadHandler;
};

