#include "TowerManager.h"

void TowerManager::addTower(const Tower::Ptr &tower) {
    tower->setTexture(m_towersTexture, m_towerTexCoords[tower->getTowerType()]);
    m_towers.push_back(tower);
}

void TowerManager::removeTower(const Tower::Ptr &tower) {
    m_towers.erase(std::find(m_towers.begin(), m_towers.end(), tower));
}

void TowerManager::initialize() {
    m_towerTexCoords[TowerType::GunTower] = {0, 0, 50, 70};
    m_towerTexCoords[TowerType::BowTower] = {50, 0, 50, 70};
    m_towerTexCoords[TowerType::IceTower] = {100, 0, 50, 70};
    m_towerTexCoords[TowerType::PoisonTower] = {150, 0, 50, 70};
    m_towerTexCoords[TowerType::FireTower] = {0, 70, 50, 70};
    m_towerTexCoords[TowerType::BombTower] = {50, 70, 50, 70};
    m_towerTexCoords[TowerType::MagicTower] = {100, 70, 50, 70};
    m_towerTexCoords[TowerType::ElectricityTower] = {150, 70, 50, 70};

    m_towersTexture.loadFromFile("asset/texture/towers.png");
}

void TowerManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &tower : m_towers) {
        target.draw(*tower, states);
    }
}

void TowerManager::handleEnemyLockOn(EnemyManager *enemyManager) {
    for (const auto& tower : m_towers) {
        if (tower->hasLockOn()) {
            tower->validateLockOn();
            continue;
        }

        enemyManager->tryGetLockOn(tower);
    }
}

void TowerManager::tick() {
    for (const auto &tower : m_towers) {
        if(tower->hasLockOn()) {
            tower->shoot();
        }
    }
}