#pragma once

#include "Tower.h"
#include "TowerManager.h"
#include "WaveManager.h"
#include "Enemy.h"
#include "EnemyManager.h"

#include <memory>
#include <functional>

#include <SFML/System/Clock.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class MainGame : public sf::Drawable, public sf::NonCopyable {

    //Checks to see what enemies can be spawned
    void spawnEnemies();

    void spawnEnemy(const Enemy::Ptr& enemy);

    unsigned int health = 100;
    unsigned int gold = 1000;

    TowerManager tower_manager;
    WaveManager wave_manager;
    EnemyManager enemy_manager;

    sf::Clock last_enemy_spawned;

public:

    MainGame() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update();

    void addGold(unsigned int amount);

    void substractGold(unsigned int amount);

    void setGold(unsigned int amount);

    unsigned int getGold() const;

    void addHealth(unsigned int health);

    void substractHealth(unsigned int health);

    void setHealth(unsigned int health);

    unsigned int getHealth() const;

    void nextWave();

    void onEnemyDestination(const Enemy::Ptr& enemy);

    void onEnemyKilled(const Enemy::Ptr& enemy);

    TowerManager *getTowerManager();

    WaveManager *getWaveManager();

    EnemyManager *getEnemyManager();
};

