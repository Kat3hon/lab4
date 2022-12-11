#include "EnemyManager.h"

void EnemyManager::initialize() {
    m_enemyTextureAtlas.loadFromFile("asset/texture/enemies.png");

    m_enemyTexCoords[EnemyType::GroundEnemy] = {0, 0, 35, 35};
    m_enemyTexCoords[EnemyType::AirEnemy] = {36, 0, 35, 35};
}

void EnemyManager::removeEnemy(const Enemy::Ptr &enemy) {
    // we add the enemy to the queue,
    // so we can remove it safely after everything is done :)
    m_enemiesToCleanUp.push_back(enemy);
}

void EnemyManager::addEnemy(const Enemy::Ptr &enemy) {
    enemy->setTexture(m_enemyTextureAtlas, m_enemyTexCoords[enemy->getType()]);
    m_enemies.push_back(enemy);
}

Enemy::Ptr EnemyManager::getMostProgressedEnemy() {
    return *std::max_element(m_enemies.begin(), m_enemies.end(), [](const Enemy::Ptr &lhs, const Enemy::Ptr &rhs) {
        return lhs->getProgress() < rhs->getProgress();
    });
}

void EnemyManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &enemy : m_enemies) {
        target.draw(*enemy, states);
    }
}

void EnemyManager::tick() {
    for (const auto &enemy : m_enemies) {
        enemy->step();
    }

    cleanUp();
}

std::size_t EnemyManager::getEnemyCount() {
    return m_enemies.size();
}

void EnemyManager::handleEnemyPathing(const Grid &grid) {
    for (const auto &enemy : m_enemies) {
        if (!enemy->needsNewPath()) {
            continue;
        }

        // to align stuff, we need to add 25 to x and y of the tile target position (since it's origin is in the left top)
        // needs to be changed at some point..

        const sf::Vector2<int> targetTileCoordinate = grid.getEnemyPathTileCoordinate(enemy->getPathingIndex() + 1);
        const sf::Vector2<float> targetPosition = grid.getTileWindowPositionFromTileCoordinate(targetTileCoordinate);

        if (sf::Vector2<float>({targetPosition.x + 25.f, targetPosition.y + 25.f}) == enemy->getPosition()) {
            // enemy reached destination
            enemy->reachGoal();
        }

        const Direction direction = grid.determineDirection(enemy->getPosition(),
                                                            {targetPosition.x + 25.f, targetPosition.y + 25.f});

        enemy->setDirection(direction, {targetPosition.x + 25.f, targetPosition.y + 25.f});
    }
}

void EnemyManager::cleanUp() {

    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [this](const Enemy::Ptr &enemy) {
        return std::find(m_enemiesToCleanUp.begin(), m_enemiesToCleanUp.end(), enemy) != m_enemiesToCleanUp.end();
    }), m_enemies.end());

    m_enemiesToCleanUp.clear();
}

void EnemyManager::tryGetLockOn(const Tower::Ptr &tower) {
    if (tower->hasLockOn()) {
        return;
    }

    auto it = std::find_if(m_enemies.begin(), m_enemies.end(), [tower](const Enemy::Ptr& enemy) {
        return tower->isInRange(enemy);
    });

    if (it == m_enemies.end()) {
        return;
    }

    tower->lockOn(*it);
}