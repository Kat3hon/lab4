#include "Lain.h"
#include "MainGame.h"

void Lain::update() {
    enemy_manager.update();
    enemy_manager.handleEnemyPathing(path);
}

void Lain::spawnEnemies(WaveManager& wave_manager, MainGame* instance) {
    // We need to check if we are eligible to spawn enemies or not.
    Wave *wave = wave_manager.getCurrentWave();
    const unsigned int spawnInterval = wave->getEnemySpawnInterval();

    if (last_enemy_spawned.getElapsedTime().asMilliseconds() >= spawnInterval && wave->getEnemyCount() > 0) {
        wave->enemyGotSpawned();
        last_enemy_spawned.restart();

        // Each wave, our enemies will have 5 more health.
        spawnEnemy(std::make_shared<Enemy>(wave_manager.getCurrentWaveNo() * 20 + 30, "Slime"), instance);
    }
}

void Lain::draw(sf::RenderTarget& target) const {
    enemy_manager.draw(target);
}

void Lain::spawnEnemy(const Enemy::Ptr &enemy, MainGame* instance) {
    enemy_manager.addEnemy(enemy);

    const sf::Vector2i spawnLocation = path.getEnemySpawnTileCoordinate();
    //const sf::Vector2f windowPosition = path.getTileWindowPositionFromTileCoordinate(spawnLocation);
    const sf::Vector2f windowPosition = {static_cast<float>(spawnLocation.x), static_cast<float>(spawnLocation.y)};

    enemy->setPosition(windowPosition.x, windowPosition.y);
    enemy->setGoalHandler(std::bind(&MainGame::onEnemyDestination, instance, std::placeholders::_1));
    enemy->setEnemyDeadHandler(std::bind(&MainGame::onEnemyKilled, instance, std::placeholders::_1));
}

EnemyManager *Lain::getEnemyManager() {
    return &enemy_manager;
}

void Lain::setPath(unsigned int num) {
    path.initialize(num);
}