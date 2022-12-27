#pragma once

#include "Enemy.h"
#include "Path.h"
#include "Tower.h"

#include <vector>
#include <algorithm>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class EnemyManager {

    void cleanUp();

    std::vector<Enemy::Ptr> enemies;
    std::vector<Enemy::Ptr> enemies_after_step;
    std::unordered_map<std::string, sf::Rect<int>> enemy_textures_coords;
    sf::Texture enemy_tileset;

public:

    EnemyManager();

    void update();

    void removeEnemy(const Enemy::Ptr &enemy);

    void addEnemy(const Enemy::Ptr &enemy);

    std::size_t getEnemyCount();

    /// Gets the enemy which is most advanced.
    Enemy::Ptr getMostProgressedEnemy();

    void handleEnemyPathing(const Path& path);

    void tryGetLockOn(const Tower::Ptr& tower);
};
