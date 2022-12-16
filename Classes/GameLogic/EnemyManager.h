#pragma once

#include "Enemy.h"
#include "../GUI/Level.h"
#include "Tower.h"

#include <vector>
#include <algorithm>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>

class EnemyManager : public sf::Drawable {

    void cleanUp();

    std::vector<Enemy::Ptr> enemies;
    std::vector<Enemy::Ptr> enemies_after_step;
    std::unordered_map<std::string, sf::Rect<int>> enemy_textures_coords;
    sf::Texture enemy_tileset;

public:

    EnemyManager();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update();

    void removeEnemy(const Enemy::Ptr &enemy);

    void addEnemy(const Enemy::Ptr &enemy);

    std::size_t getEnemyCount();

    // Gets the enemy which is most advanced.
    Enemy::Ptr getMostProgressedEnemy();

    //void handleEnemyPathing(const Level& map);

    void tryGetLockOn(const Tower::Ptr& tower);
};
