//
// Created by kklim on 17.12.2022.
//

#include "WeaponGUI.h"

WeaponGUI::WeaponGUI(ElementType elementType, float x, float y) :
    selected(false), is_built(false) {
    weapon = std::make_shared<Weapon>(elementType);
    radius_shape.setFillColor(sf::Color{235, 79, 52, 128});
}

void WeaponGUI::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= sf::Transformable::getTransform();

    if (selected || !is_built)
        target.draw(radius_shape, states);

    target.draw(sprite, states);
}

void WeaponGUI::setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords) {
    sprite.setTexture(texture);
    sprite.setTextureRect(textureCoords);
}

void WeaponGUI::setSelected(bool selected_var) {
    selected = selected_var;

    radius_shape.setPosition(TILE_SIZE / 2.f, TILE_SIZE / 2.f + 75 - TILE_SIZE); //???
    radius_shape.setRadius(static_cast<float>(weapon->getRange() * TILE_SIZE)); //??
    radius_shape.setOrigin(radius_shape.getRadius(), radius_shape.getRadius());
}

void WeaponGUI::build() {
    is_built = true;
}

bool WeaponGUI::isBuilt() const {
    return is_built;
}

Weapon::Ptr WeaponGUI::getWeapon() const {
    return weapon;
}