#pragma once

#include "Enemy.h"
#include "WaveManager.h"
#include "EnemyManager.h"

class Lain {

    EnemyManager enemy_manager;

    void spawnEnemy(const Enemy::Ptr& enemy);

    sf::Clock last_enemy_spawned;

    Path path;

public:

    Lain() = default;

    void nextWave();

    WaveManager *getWaveManager();

    EnemyManager *getEnemyManager();

    void update();

    void spawnEnemies(WaveManager &wave_manager);

    void setPath(Tile& start, Tile& end, std::vector<Tile> path_vec) {
        path.setPath(start, end, path_vec);
    }
};

