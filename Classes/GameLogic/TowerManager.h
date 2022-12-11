#include "Tower.h"
#include "TowerType.h"
#include "../enemy/enemyManager.hpp"

#include <vector>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class TowerManager : public sf::Drawable {
public:
    void initialize();

    void tick();

    void addTower(const Tower::Ptr &tower);

    void removeTower(const Tower::Ptr &tower);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void handleEnemyLockOn(EnemyManager* enemyManager);
private:

    std::vector<Tower::Ptr> m_towers;
    std::unordered_map<TowerType, sf::Rect<int>> m_towerTexCoords;
    sf::Texture m_towersTexture;
};
