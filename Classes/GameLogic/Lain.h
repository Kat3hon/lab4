#pragma once

#include "Enemy.h"
#include "WaveManager.h"
#include "EnemyManager.h"

class Lain {

    EnemyManager enemy_manager;
    WaveManager wave_manager;

    void spawnEnemy(const Enemy::Ptr& enemy);

    sf::Clock last_enemy_spawned;

public:

    Lain() = default;

    void nextWave();

    WaveManager *getWaveManager();

    EnemyManager *getEnemyManager();

    void update();

//Checks to see what enemies can be spawned
void spawnEnemies();
};

