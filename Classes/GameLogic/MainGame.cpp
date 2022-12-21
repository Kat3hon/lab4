#include "MainGame.h"

#include <functional>

void MainGame::update() {
    for (auto &it : lains) {
        it.update();
        weapon_manager.update();
        weapon_manager.handleEnemyLockOn(it.getEnemyManager());
        it.spawnEnemies();
    }
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

WeaponManager *MainGame::getWeaponManager() {
    return &weapon_manager;
}

void MainGame::onEnemyKilled(const Enemy::Ptr &enemy) {
    for (auto& it: lains) {
        it.getEnemyManager()->removeEnemy(enemy);
        addGold(lains[0].getWaveManager()->getCurrentWaveNo() * 5 + 5);
    }
}

void MainGame::onEnemyDestination(const Enemy::Ptr &enemy) {
    castle.substractHealth(enemy->getHealth());
    for (auto& it: lains) {
        it.getEnemyManager()->removeEnemy(enemy);
    }
}

