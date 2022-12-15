#include "MainGame.h"

#include <functional>

MainGame::MainGame() : health(100), gold(1000) {
    m_grid.initialize();
    enemy_manager.initialize();
}

void MainGame::tick() {
    enemy_manager.update();
    tower_manager.update();

    enemy_manager.handleEnemyPathing(m_grid);
    tower_manager.handleEnemyLockOn(&enemy_manager);
    spawnEnemies();
}

void MainGame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // bottom layer (tiles)
    target.draw(m_grid, states);

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

unsigned int MainGame::getGold() const {
    return gold;
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

unsigned int MainGame::getHealth() const {
    return health;
}

void MainGame::setHealth(unsigned int health) {
    health = health;
}

MainGame *MainGame::getGrid() {
    return &m_grid;
}

void MainGame::handleTileClick(const Tile::Ptr &tile) {

    if(hasTowerSelected())
        getSelectedTower()->setSelected(false);

    // we have nothing to do here
    if (!tile->isBuildable()) {
        current_tower.reset();
        return;
    }

//    current_tower = std::make_shared<Tower>(TowerType::ElectroTower);

    if (!tile->hasTower() && hasTowerSelected() && !current_tower->isBuilt()) {

        // for now let each tower cost a 100
        if (getGold() < 100) {
            current_tower.reset();
            return;
        }

        substractGold(100);

        tile->setTower(current_tower);
        tower_manager.push(current_tower);

        // Since the tower is bigger than the actual tile. A tower equals to 70 pixels on the Y axis. Time to substract that
        // So it actually looks that the tower is on the tile.
        sf::Vector2<float> towerPosition = m_grid.getTileWindowPosition(tile);
        current_tower->setPosition(towerPosition.x, towerPosition.y - (70 - TILE_SIZE));
        current_tower->setSelected(true);
        current_tower->build();

        return;
    }

    // Seems like there already is a tower built on this spot.
    // We might want to upgrade this tower.
    // Select the tower and open the upgrade
    if (tile->hasTower()) {

        if (hasTowerSelected()) {
            deselectTower();
        }

        current_tower = tile->getTower();
        current_tower->setSelected(true);
        return;
    }
}

bool MainGame::hasTowerSelected() {
    return current_tower != nullptr;
}

Tower::Ptr MainGame::getSelectedTower() const {
    return current_tower;
}

TowerManager *MainGame::getTowerManager() const {
    return &tower_manager;
}

WaveManager *MainGame::getWaveManager() const {
    return &wave_manager;
}

void MainGame::nextWave() {
    wave_manager.forceWave();
}

EnemyManager *MainGame::getEnemyManager() const {
    return &enemy_manager;
}

void MainGame::spawnEnemies() {
    // We need to check if we are eligible to spawn enemies or not.
    Wave *wave = wave_manager.getCurrentWave();
    const unsigned int spawnInterval = wave->getEnemySpawnInterval();

    if (last_enemy_spawned.getElapsedTime().asMilliseconds() >= spawnInterval && wave->getEnemyCount() > 0) {
        wave->enemyGotSpawned();
        last_enemy_spawned.restart();

        // other wave will just be a regular ground enemies
        // also, we don't seed the random
        // we want our games to always be the same, right?

        EnemyType enemyType = EnemyType::GroundEnemy;

        if (wave_manager.getCurrentWaveNo() % 3 == 0) {
            // flying wave, spawn flying enemy
            enemyType = EnemyType::AirEnemy;
        }

        if (wave_manager.getCurrentWaveNo() % 10 == 0) {
            // boss wave, spawn random enemies, with a boss.
            // we mod it by 2, because we only have 2 enemy types (for now)
            enemyType = rand() % 2 == 0 ? EnemyType::GroundEnemy : EnemyType::AirEnemy;
        }

        // Each wave, our enemies will have 5 more health.
        spawnEnemy(std::make_shared<Enemy>(wave_manager.getCurrentWaveNo() * 5 + 30, enemyType));
    }
}

void MainGame::spawnEnemy(const Enemy::Ptr &enemy) {
    enemy_manager.addEnemy(enemy);

    const sf::Vector2i spawnLocation = m_grid.getEnemySpawnTileCoordinate();
    const sf::Vector2f windowPosition = m_grid.getTileWindowPositionFromTileCoordinate(spawnLocation);

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

void MainGame::deselectTower() {
    current_tower->setSelected(false);
    current_tower.reset();
}

void MainGame::onEnemyKilled(const Enemy::Ptr &enemy) {
    enemy_manager.removeEnemy(enemy);

    addGold(wave_manager.getCurrentWaveNo() * 5 + 5);
}

void MainGame::selectTower(const Tower::Ptr &tower) {
    current_tower = tower;
}