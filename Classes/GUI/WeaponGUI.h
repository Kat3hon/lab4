#pragma once

#include "../GameLogic/Weapon.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>

class WeaponGUI: public GameObject {

    bool is_built;

    /// Sprite of the tower.
    sf::Sprite sprite;

    /// Since tower is selected, its radius will be rendered.
    sf::CircleShape radius_shape;

    /// Checks weapon is selected or not.
    bool selected;

    std::unique_ptr<Weapon> weapon;

public:
    using Ptr = std::shared_ptr<WeaponGUI>;

    explicit WeaponGUI(ElementType elementType);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords);
    void setSelected(bool selected_var);
    void build();
    bool isBuilt() const;
};


#endif //LAB4_WEAPONGUI_H
