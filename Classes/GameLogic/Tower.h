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

    bool is_built;

    /// Range of the tower. Attack radius.
    unsigned int range;

    /// Damage of the tower.
    unsigned int damage;

    /// Fire rate of the tower, in milliseconds.
    /// 1000 means 1 projectile a second
    /// 500 means 2 projectiles a second...
    unsigned int fire_rate;

    /// Sprite of the tower.
    sf::Sprite sprite;

    /// Since tower is selected, its radius will be rendered.
    sf::CircleShape radius_shape;

    /// Checks tower is selected or not.
    bool selected;

    /// Type of tower: Hydro, Dendro, Cryo, Pyro or Electro.
    TowerType type;

    std::vector<ITower> interfaces;

    /// Currently focused enemy
    std::weak_ptr<Enemy> curr_focussed_enemy;

    // Last time this tower shot
    sf::Clock timeof_last_shot;

public:
    explicit Tower(TowerType towerType);

    using Ptr = std::shared_ptr<Tower>;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setSelected(bool selected);

    bool hasLockOn();

    /// this function will be used
    /// to check if the enemy is still in range of tower radius.
    /// if not, deselect the current focused enemy.
    void validateLockOn();

    Enemy::Ptr getLockOn();

    void lockOn(std::weak_ptr<Enemy> enemy);

    void shoot();

    void build();

    bool isBuilt() const;

    bool isInRange(const Enemy::Ptr& enemy);

    unsigned int getRange() const;

    unsigned int getDamage() const;

    unsigned int getFireRate() const;

    TowerType getTowerType() const;

    void setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords);
};

