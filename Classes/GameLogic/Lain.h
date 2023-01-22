#pragma once

#include "Enemy.h"
#include "WaveManager.h"
#include "EnemyManager.h"
#include "MainGame.h"

class MainGame;

class Lain {

    EnemyManager enemy_manager;

    void spawnEnemy(const Enemy::Ptr& enemy, MainGame* instance);

    sf::Clock last_enemy_spawned;

    Path path;

public:

    Lain() = default;

    EnemyManager *getEnemyManager();

    void update();

    void spawnEnemies(WaveManager &wave_manager, MainGame* instance);

    void draw(sf::RenderTarget &target) const;

    void setPath(unsigned int num);
};

