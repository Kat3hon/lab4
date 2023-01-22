#include "MainGame.h"

#include <functional>
#include <iostream>

void MainGame::update() {
    for (auto &it : lains) {
        it.update();
        weapon_manager.update();
        it.spawnEnemies(wave_manager, this);
        weapon_manager.handleEnemyLockOn(it.getEnemyManager());
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

WeaponManager * MainGame::getWeaponManager() {
    return &weapon_manager;
}

WaveManager * MainGame::getWaveManager() {
    return &wave_manager;
}

void MainGame::onEnemyKilled(const Enemy::Ptr &enemy) {
    for (auto& it: lains) {
        it.getEnemyManager()->removeEnemy(enemy);
    }
    addGold(wave_manager.getCurrentWaveNo() * 5 + 5);
}

void MainGame::onEnemyDestination(const Enemy::Ptr &enemy) {
    castle.substractHealth(enemy->getHealth());
    for (auto &it: lains) {
        it.getEnemyManager()->removeEnemy(enemy);
    }
}

Castle MainGame::getCastle() const {
    return castle;
}

std::vector<Lain> MainGame::getLains() const {
    return lains;
}

bool MainGame::canBeCompressedTile(const std::vector<Tile>& vec, int x, int y) {
    bool first = false, second = false, third = false;
    for (const auto& tile: vec) {
        if (tile.getType() == typePath && tile.getX() == x+tile.TILE_SIZE && tile.getY() == y)
            first = true;
        if (tile.getType() == typePath && tile.getX() == x && tile.getY() == y+tile.TILE_SIZE)
            second = true;
        if (tile.getType() == typePath && tile.getX() == x+tile.TILE_SIZE && tile.getY() == y+tile.TILE_SIZE)
            third = true;
    }
    return first && second && third;
}

void MainGame::setPath(const std::vector<Tile>& vec, unsigned int width, unsigned int height) {
    int count_lains_tiles = 0;
    std::vector<sf::Vector2<int>> compressed_tiles;
    std::vector<sf::Vector2<int>> pathing_points;
    for (const auto& tile : vec) {
        if (tile.getType() == typeLain)
            count_lains_tiles++;
        if (canBeCompressedTile(vec, tile.getX(), tile.getY()))
            compressed_tiles.emplace_back(tile.getX()+tile.TILE_SIZE, tile.getY()+tile.TILE_SIZE);
    }
    int count_lains = count_lains_tiles/4;
    for (int i = 0; i < count_lains; ++i) {
        lains.emplace_back();
    }

    lains[0].setPath(0);
    lains[1].setPath(1);
    //hardcode

}

void MainGame::nextWave() {
    wave_manager.forceWave();
}






