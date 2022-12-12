#include "GameObject.h"
#include "TowerType.h"
#include "Enemy.h"
#include "ITower.h"

#include <memory>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>

class Tower : public GameObject {
public:
    explicit Tower(TowerType towerType);

    using Ptr = std::shared_ptr<Tower>;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setSelected(bool selected);

    bool hasLockOn();

    void validateLockOn();

    Enemy::Ptr getLockOn();

    void lockOn(std::weak_ptr<Enemy> enemy);

    void shoot();

    void build();

    bool isBuilt();

    bool isInRange(const Enemy::Ptr& enemy);

    unsigned int getRange();

    unsigned int getDamage();

    unsigned int getFireRate();

    TowerType getTowerType();

    void setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords);

private:

    bool m_isBuilt;

    // The range of the tower
    // this will be the radius of a circle
    unsigned int m_range;

    // Damage the tower will be doing
    // each shot
    unsigned int m_damage;

    // FireTower rate of the tower, in milliseconds.
    // 1000 means 1 bullet a second
    // 500 means 2 bullets a second.. etc
    unsigned int m_fireRate;

    // Sprite of the turret.
    // Texture and texture coords will be provider by tower manager
    sf::Sprite m_sprite;

    // If this tower is selected, this will be rendered
    sf::CircleShape m_radiusShape;

    // if the tower is selected or not, if it's selected
    // it will draw the radius around the tower
    bool m_selected;

    // Type of tower
    TowerType m_type;

    std::vector<ITower> m_components;

    // Currently focused enemy
    std::weak_ptr<Enemy> m_focussedEnemy;

    // Last time this tower shot
    sf::Clock m_lastShot;
};

