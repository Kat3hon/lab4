#include "WeaponManager.h"

WeaponManager::WeaponManager() {
    towers_textures_coords[ElementType::Hydro] = {0, 0, 50, 70};
    towers_textures_coords[ElementType::Dendro] = {50, 0, 50, 70};
    towers_textures_coords[ElementType::Cryo] = {100, 0, 50, 70};
    towers_textures_coords[ElementType::Pyro] = {150, 0, 50, 70};
    towers_textures_coords[ElementType::Electro] = {0, 70, 50, 70};

    trap_textures_coords[ElementType::Hydro] = {};
    trap_textures_coords[ElementType::Dendro] = {};
    trap_textures_coords[ElementType::Cryo] = {};
    trap_textures_coords[ElementType::Pyro] = {};
    trap_textures_coords[ElementType::Electro] = {};

    if (!tileset.loadFromFile("asset/texture/weapons.png")) {
        MessageBox(nullptr, "Can not load weapons.png", "Error!", MB_OK);
        return;
    }
}

void WeaponManager::push(const Weapon::Ptr &weapon) {
    weapon->setTexture(tileset, towers_textures_coords[weapon->getElementType()]);
    weapons.push_back(weapon);
}

void WeaponManager::pop(const Weapon::Ptr &weapon) {
    weapons.erase(std::find(weapons.begin(), weapons.end(), weapon));
}

void WeaponManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &tower : weapons)
        target.draw(*tower, states);
}

void WeaponManager::handleEnemyLockOn(EnemyManager *enemyManager) {
    for (const auto& tower : weapons) {
        if (tower->hasLockOn()) {
            tower->validateLockOn();
            continue;
        }
        enemyManager->tryGetLockOn(tower);
    }
}

void WeaponManager::update() {
    for (const auto &tower : weapons)
        if(tower->hasLockOn())
            tower->attack();
}