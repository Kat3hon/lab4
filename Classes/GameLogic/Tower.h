#pragma once

#include "../GUI/GameObject.h"
#include "ElementType.h"
#include "Enemy.h"
#include "IWeapon.h"
#include "Weapon.h"

#include <memory>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>

class Tower : public Weapon {

    /// Fire rate of the tower, in milliseconds.
    /// 1000 means 1 projectile a second
    /// 500 means 2 projectiles a second...
    unsigned int fire_rate;

    /// Last time this tower shot.
    sf::Clock timeof_last_shot;

public:

    explicit Tower(ElementType elementType);
    unsigned int getFireRate() const;
    void attack() override;
};

