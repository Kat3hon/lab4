#pragma once

#include "Enemy.h"
#include "Path.h"
#include "Tower.h"

#include <vector>
#include <algorithm>
#include <unordered_map>

class EnemyManager  {

    void cleanUp();

    std::vector<Enemy::Ptr> enemies;
    std::vector<Enemy::Ptr> enemies_after_step;
//    std::unordered_map<std::string, sf::Rect<int>> enemy_textures_coords;
//    sf::Texture enemy_tileset;

public:

    EnemyManager();

//    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update();

    void removeEnemy(const Enemy::Ptr &enemy);

    void addEnemy(const Enemy::Ptr &enemy);

    std::size_t getEnemyCount();

    /// Gets the enemy which is most advanced.
    Enemy::Ptr getMostProgressedEnemy();

    void handleEnemyPathing(const class Path& path);

    void tryGetLockOn(const Tower::Ptr& tower);
};
