#pragma once

#include "../GameLogic/Weapon.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Transformable.hpp>

class WeaponGUI: public GameObject {

    bool is_built;

    float tile_width;

    float tile_height;

    /// Sprite of the tower.
    sf::Sprite sprite;

    /// Since tower is selected, its radius will be rendered.
    sf::CircleShape radius_shape;

    /// Checks weapon is selected or not.
    bool selected;

    std::shared_ptr<Weapon> weapon;

public:
    using Ptr = std::shared_ptr<WeaponGUI>;

    explicit WeaponGUI(ElementType elementType, float x, float y);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords);
    void setSelected(bool selected_var);
    void build();
    bool isBuilt() const;
    Weapon::Ptr getWeapon() const;

};
