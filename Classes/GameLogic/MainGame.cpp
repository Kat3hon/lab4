#include "MainGame.h"

#include <functional>

void MainGame::update() {
    for (auto &it : lains) {
        it.update();
        weapon_manager.update();
        weapon_manager.handleEnemyLockOn(it.getEnemyManager());
        it.spawnEnemies(wave_manager);
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

void MainGame::setPath(const std::vector<Tile>& vec) {
    //находим 4 тайла, у которых одинаковые стороны и тип убежище
    //это убежище, старт для графа
    std::vector<Tile> lain_tiles;
    std::vector<Tile> path_tiles;
    std::vector<Tile> castle_tiles;
    for (auto& tile: vec) {
        if (tile.getType() == typeLain)
            lain_tiles.push_back(tile);
        if (tile.getType() == typeCastle)
            castle_tiles.push_back(tile);
        if (tile.getType() == typePath)
            path_tiles.push_back(tile);
    }
    // самостоятельно посчитать кол-во лейнов
    lains.emplace_back(Lain());
    lains.emplace_back((Lain()));

    Tile source1;
    Tile source2;

    Tile dist;
    for (auto& pt: path_tiles) {
        if (abs(pt.getX()-lain_tiles[0].getX()) == pt.TILE_SIZE ||
            abs(pt.getY()-lain_tiles[0].getY()) == pt.TILE_SIZE) {
            source1 = pt;
            break;
        }
    }
    for (auto& pt: path_tiles) {
        if (abs(pt.getX()-lain_tiles[3].getX()) == pt.TILE_SIZE ||
            abs(pt.getY()-lain_tiles[3].getY()) == pt.TILE_SIZE) {
            source2 = pt;
            break;
        }
    }

    for (auto& pt: path_tiles) {
        if (abs(pt.getX()-castle_tiles[0].getX()) == pt.TILE_SIZE ||
            abs(pt.getY()-castle_tiles[0].getY()) == pt.TILE_SIZE) {
            dist = pt;
            break;
        }
    }

    lains[0].setPath(source1, dist, path_tiles);
    lains[1].setPath(source2, dist, path_tiles);

}

void MainGame::nextWave() {
    wave_manager.forceWave();
}





