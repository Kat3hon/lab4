#include "MainGame.h"

#include <functional>

MainGame::MainGame() : m_health(100), m_gold(1000) {
    m_grid.initialize();
    m_towerManager.initialize();
    m_enemyManager.initialize();
}

void MainGame::tick() {
    m_enemyManager.tick();
    m_towerManager.tick();

    m_enemyManager.handleEnemyPathing(m_grid);
    m_towerManager.handleEnemyLockOn(&m_enemyManager);
    spawnEnemies();
}

void MainGame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // bottom layer (tiles)
    target.draw(m_grid, states);

    // enemy layer
    target.draw(m_enemyManager, states);

    // tower layer
    target.draw(m_towerManager, states);
}

void MainGame::addGold(unsigned int amount) {
    m_gold += amount;
}

void MainGame::substractGold(unsigned int amount) {
    if (amount > m_gold) {
        m_gold = 0;
        return;
    }

    m_gold -= amount;
}

void MainGame::setGold(unsigned int amount) {
    m_gold = amount;
}

unsigned int MainGame::getGold() {
    return m_gold;
}

void MainGame::addHealth(unsigned int health) {
    m_health += health;
}

void MainGame::substractHealth(unsigned int health) {
    if (health > m_health) {
        m_health = 0;
        return;
    }

    m_health -= health;
}

unsigned int MainGame::getHealth() {
    return m_health;
}

void MainGame::setHealth(unsigned int health) {
    m_health = health;
}

MainGame *MainGame::getGrid() {
    return &m_grid;
}

void MainGame::handleTileClick(const Tile::Ptr &tile) {

    if(hasTowerSelected()) {
        getSelectedTower()->setSelected(false);
    }

    // we have nothing to do here
    if (!tile->isBuildable()) {
        m_currentSelectedTower.reset();
        return;
    }

//    m_currentSelectedTower = std::make_shared<Tower>(TowerType::ElectricityTower);

    if (!tile->hasTower() && hasTowerSelected() && !m_currentSelectedTower->isBuilt()) {

        // for now let each tower cost a 100
        if (getGold() < 100) {
            m_currentSelectedTower.reset();
            return;
        }

        substractGold(100);

        tile->setTower(m_currentSelectedTower);
        m_towerManager.addTower(m_currentSelectedTower);

        // Since the tower is bigger than the actual tile. A tower equals to 70 pixels on the Y axis. Time to substract that
        // So it actually looks that the tower is on the tile.
        sf::Vector2<float> towerPosition = m_grid.getTileWindowPosition(tile);
        m_currentSelectedTower->setPosition(towerPosition.x, towerPosition.y - (70 - TILE_SIZE));
        m_currentSelectedTower->setSelected(true);
        m_currentSelectedTower->build();

        return;
    }

    // Seems like there already is a tower built on this spot.
    // We might want to upgrade this tower.
    // Select the tower and open the upgrade
    if (tile->hasTower()) {

        if (hasTowerSelected()) {
            deselectTower();
        }

        m_currentSelectedTower = tile->getTower();
        m_currentSelectedTower->setSelected(true);
        return;
    }
}

bool MainGame::hasTowerSelected() {
    return m_currentSelectedTower != nullptr;
}

Tower::Ptr MainGame::getSelectedTower() {
    return m_currentSelectedTower;
}

TowerManager *MainGame::getTowerManager() {
    return &m_towerManager;
}

WaveManager *MainGame::getWaveManager() {
    return &m_waveManager;
}

void MainGame::nextWave() {
    m_waveManager.forceWave();
}

EnemyManager *MainGame::getEnemyManager() {
    return &m_enemyManager;
}

void MainGame::spawnEnemies() {
    // We need to check if we are eligible to spawn enemies or not.
    Wave *wave = m_waveManager.getCurrentWave();
    const unsigned int spawnInterval = wave->getEnemySpawnInterval();

    if (m_lastEnemySpawned.getElapsedTime().asMilliseconds() >= spawnInterval && wave->getEnemyCount() > 0) {
        wave->enemyGotSpawned();
        m_lastEnemySpawned.restart();

        // other wave will just be a regular ground enemies
        // also, we don't seed the random
        // we want our games to always be the same, right?

        EnemyType enemyType = EnemyType::GroundEnemy;

        if (m_waveManager.getCurrentWaveNo() % 3 == 0) {
            // flying wave, spawn flying enemy
            enemyType = EnemyType::AirEnemy;
        }

        if (m_waveManager.getCurrentWaveNo() % 10 == 0) {
            // boss wave, spawn random enemies, with a boss.
            // we mod it by 2, because we only have 2 enemy types (for now)
            enemyType = rand() % 2 == 0 ? EnemyType::GroundEnemy : EnemyType::AirEnemy;
        }

        // Each wave, our enemies will have 5 more health.
        spawnEnemy(std::make_shared<Enemy>(m_waveManager.getCurrentWaveNo() * 5 + 30, enemyType));
    }
}

void MainGame::spawnEnemy(const Enemy::Ptr &enemy) {
    m_enemyManager.addEnemy(enemy);

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
    substractHealth(1);
    m_enemyManager.removeEnemy(enemy);
}

void MainGame::deselectTower() {
    m_currentSelectedTower->setSelected(false);
    m_currentSelectedTower.reset();
}

void MainGame::onEnemyKilled(const Enemy::Ptr &enemy) {
    m_enemyManager.removeEnemy(enemy);

    addGold(m_waveManager.getCurrentWaveNo() * 5 + 5);
}

void MainGame::selectTower(const Tower::Ptr &tower) {
    m_currentSelectedTower = tower;
}