#include "Lain.h"

void Lain::update() {
    enemy_manager.update();
    //enemy_manager.handleEnemyPathing(path);
}

void Lain::spawnEnemies(WaveManager& wave_manager) {
    // We need to check if we are eligible to spawn enemies or not.
    Wave *wave = wave_manager.getCurrentWave();
    const unsigned int spawnInterval = wave->getEnemySpawnInterval();

    if (last_enemy_spawned.getElapsedTime().asMilliseconds() >= spawnInterval && wave->getEnemyCount() > 0) {
        wave->enemyGotSpawned();
        last_enemy_spawned.restart();

        // Each wave, our enemies will have 5 more health.
        spawnEnemy(std::make_shared<Enemy>(wave_manager.getCurrentWaveNo() * 5 + 30));
    }
}

void Lain::spawnEnemy(const Enemy::Ptr &enemy) {
//    enemy_manager.addEnemy(enemy);
//
//    const sf::Vector2i spawnLocation = map.getEnemySpawnTileCoordinate();
//    const sf::Vector2f windowPosition = map.getTileWindowPositionFromTileCoordinate(spawnLocation);
//
//    // we know that our enemy has a width of 35, and the tiles a width of 50.
//    // 50 - 35 = 15 space left, divide that by 2, and we get a 7.5
//    // BUT. Our enemy origin is in the center, meaning, that we also need to add
//    // an additional 35 / 2 = 17.5 to the calculation.
//    // We need to center our spawned enemy in the center of the tile.
//    // And we always do these calculations relative to the top left side of the tile
//    enemy->setPosition(windowPosition.x + 25.f, windowPosition.y + 25.f);
//    enemy->setGoalHandler(std::bind(&MainGame::onEnemyDestination, this, std::placeholders::_1));
//    enemy->setEnemyDeadHandler([this](auto && PH1) { onEnemyKilled(std::forward<decltype(PH1)>(PH1)); });
}

EnemyManager *Lain::getEnemyManager() {
    return &enemy_manager;
}