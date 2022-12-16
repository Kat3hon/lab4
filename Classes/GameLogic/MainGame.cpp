#include "MainGame.h"

#include <functional>

void MainGame::update() {
    enemy_manager.update();
    tower_manager.update();

    enemy_manager.handleEnemyPathing(map);
    tower_manager.handleEnemyLockOn(&enemy_manager);
    spawnEnemies();
}

void MainGame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // bottom layer (tiles)
    target.draw(map, states);

    // enemy layer
    target.draw(enemy_manager, states);

    // tower layer
    target.draw(tower_manager, states);
}

void MainGame::addGold(unsigned int amount) {
    gold += amount;
}

void MainGame::substractGold(unsigned int amount) {
    if (amount > gold) {
        gold = 0;
        return;
    }

    gold -= amount;
}

void MainGame::setGold(unsigned int amount) {
    gold = amount;
}

void MainGame::addHealth(unsigned int health_var) {
    health += health_var;
}

void MainGame::substractHealth(unsigned int health_var) {
    if (health_var > health) {
        health = 0;
        return;
    }

    health -= health;
}

void MainGame::setHealth(unsigned int health_var) {
    health = health_var;
}

void MainGame::nextWave() {
    wave_manager.forceWave();
}

void MainGame::spawnEnemies() {
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

void MainGame::spawnEnemy(const Enemy::Ptr &enemy) {
    enemy_manager.addEnemy(enemy);

    const sf::Vector2i spawnLocation = map.getEnemySpawnTileCoordinate();
    const sf::Vector2f windowPosition = map.getTileWindowPositionFromTileCoordinate(spawnLocation);

    // we know that our enemy has a width of 35, and the tiles a width of 50.
    // 50 - 35 = 15 space left, divide that by 2, and we get a 7.5
    // BUT. Our enemy origin is in the center, meaning, that we also need to add
    // an additional 35 / 2 = 17.5 to the calculation.
    // We need to center our spawned enemy in the center of the tile.
    // And we always do these calculations relative to the top left side of the tile
    enemy->setPosition(windowPosition.x + 25.f, windowPosition.y + 25.f);
    enemy->setGoalHandler(std::bind(&MainGame::onEnemyDestination, this, std::placeholders::_1));
    enemy->setEnemyDeadHandler(std::bind(&MainGame::onEnemyKilled, this, std::placeholders::_1));
}

void MainGame::onEnemyDestination(const Enemy::Ptr &enemy) {
    substractHealth(enemy->getHealth());
    enemy_manager.removeEnemy(enemy);
}

void MainGame::onEnemyKilled(const Enemy::Ptr &enemy) {
    enemy_manager.removeEnemy(enemy);

    addGold(wave_manager.getCurrentWaveNo() * 5 + 5);
}

unsigned int MainGame::getGold() const {
    return gold;
}

unsigned int MainGame::getHealth() const {
    return health;
}

WeaponManager *MainGame::getWeaponManager() {
    return &weapon_manager;
}

WaveManager *MainGame::getWaveManager() {
    return &wave_manager;
}

EnemyManager *MainGame::getEnemyManager() {
    return &enemy_manager;
}

