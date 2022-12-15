#include "TowerManager.h"

TowerManager::TowerManager() {
    towers_textures_coords[TowerType::HydroTower] = {0, 0, 50, 70};
    towers_textures_coords[TowerType::DendroTower] = {50, 0, 50, 70};
    towers_textures_coords[TowerType::CryoTower] = {100, 0, 50, 70};
    towers_textures_coords[TowerType::PyroTower] = {150, 0, 50, 70};
    towers_textures_coords[TowerType::ElectroTower] = {0, 70, 50, 70};

    if (!towers_tileset.loadFromFile("asset/texture/towers.png")) {
        MessageBox(nullptr, "Can not load towers.png", "Error!", MB_OK);
        return;
    }
}

void TowerManager::push(const Tower::Ptr &tower) {
    tower->setTexture(towers_tileset, towers_textures_coords[tower->getTowerType()]);
    towers.push_back(tower);
}

void TowerManager::pop(const Tower::Ptr &tower) {
    towers.erase(std::find(towers.begin(), towers.end(), tower));
}

void TowerManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &tower : towers)
        target.draw(*tower, states);
}

void TowerManager::handleEnemyLockOn(EnemyManager *enemyManager) {
    for (const auto& tower : towers) {
        if (tower->hasLockOn()) {
            tower->validateLockOn();
            continue;
        }

        enemyManager->tryGetLockOn(tower);
    }
}

void TowerManager::update() {
    for (const auto &tower : towers)
        if(tower->hasLockOn())
            tower->shoot();
}