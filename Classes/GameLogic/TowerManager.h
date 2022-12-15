#include "Tower.h"
#include "TowerType.h"
#include "EnemyManager.h"

#include <vector>
#include <unordered_map>
#include <windows.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class TowerManager : public sf::Drawable {

    std::vector<Tower::Ptr> towers;
    std::unordered_map<TowerType, sf::Rect<int>> towers_textures_coords;
    sf::Texture towers_tileset;

public:
    TowerManager();

    void update();

    void push(const Tower::Ptr &tower);

    void pop(const Tower::Ptr &tower);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void handleEnemyLockOn(EnemyManager* enemyManager);
};
