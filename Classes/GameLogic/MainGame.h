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

    unsigned int health;
    unsigned int gold;

    Grid m_grid;

    TowerManager tower_manager;
    WaveManager wave_manager;
    EnemyManager enemy_manager;

    Tower::Ptr current_tower;

    sf::Clock last_enemy_spawned;

public:

    MainGame();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void tick();

    void addGold(unsigned int amount);

    void substractGold(unsigned int amount);

    void setGold(unsigned int amount);

    unsigned int getGold() const;

    void addHealth(unsigned int health);

    void substractHealth(unsigned int health);

    void setHealth(unsigned int health);

    unsigned int getHealth() const;

    void nextWave();

    Grid *getGrid();

    void selectTower(const Tower::Ptr& tower);

    void handleTileClick(const Tile::Ptr &tile);

    void deselectTower();

    bool hasTowerSelected();

    void onEnemyDestination(const Enemy::Ptr& enemy);

    void onEnemyKilled(const Enemy::Ptr& enemy);

    Tower::Ptr getSelectedTower() const;

    TowerManager *getTowerManager() const;

    WaveManager *getWaveManager() const;

    EnemyManager *getEnemyManager() const;
};

