#include "EnemyManager.h"

EnemyManager::EnemyManager() {
    enemy_textures_coords["Slime"] = {0, 0, 35, 35};
    enemy_tileset.loadFromFile("asset/texture/enemies.png");
}

void EnemyManager::removeEnemy(const Enemy::Ptr &enemy) {
    // we add the enemy to the queue,
    // so we can remove it safely after everything is done :)
    enemies_after_step.push_back(enemy);
}

void EnemyManager::addEnemy(const Enemy::Ptr &enemy) {
    //enemy->setTexture(enemy_tileset, enemy_textures_coords[enemy->getName()]);
    enemies.push_back(enemy);
}

Enemy::Ptr EnemyManager::getMostProgressedEnemy() {
    return *std::max_element(enemies.begin(), enemies.end(), [](const Enemy::Ptr &lhs, const Enemy::Ptr &rhs) {
        return lhs->getProgress() < rhs->getProgress();
    });
}

//void EnemyManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//    for (const auto &enemy : enemies)
//        target.draw(*enemy, states);
//}

void EnemyManager::update() {
    for (const auto &enemy : enemies)
        enemy->step();

    cleanUp();
}

std::size_t EnemyManager::getEnemyCount() {
    return enemies.size();
}

//void EnemyManager::handleEnemyPathing(const Level &map) {
//    for (const auto &enemy : enemies) {
//        if (!enemy->needsNewPath())
//            continue;
//
//        // to align stuff, we need to add 25 to x and y of the tile target position (since it's origin is in the left top)
//        // needs to be changed at some point..
//
//        const sf::Vector2<int> targetTileCoordinate = map.getEnemyPathTileCoordinate(enemy->getPathingIndex() + 1);
//        const sf::Vector2<float> targetPosition = map.getTileWindowPositionFromTileCoordinate(targetTileCoordinate);
//
//        if (sf::Vector2<float>({targetPosition.x + 25.f, targetPosition.y + 25.f}) == enemy->getPosition()) {
//            // enemy reached destination
//            enemy->reachGoal();
//        }
//
//        const Direction direction = map.determineDirection(enemy->getPosition(),
//                                                           {targetPosition.x + 25.f, targetPosition.y + 25.f});
//
//        enemy->setDirection(direction, {targetPosition.x + 25.f, targetPosition.y + 25.f});
//    }
//}

void EnemyManager::cleanUp() {

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [this](const Enemy::Ptr &enemy) {
        return std::find(enemies_after_step.begin(), enemies_after_step.end(), enemy) != enemies_after_step.end();
    }), enemies.end());

    enemies_after_step.clear();
}

void EnemyManager::tryGetLockOn(const Tower::Ptr &tower) {
    if (tower->hasLockOn())
        return;

    auto it = std::find_if(enemies.begin(), enemies.end(), [tower](const Enemy::Ptr& enemy) {
        return tower->isInRange(enemy);
    });

    if (it == enemies.end())
        return;

    tower->lockOn(*it);
}