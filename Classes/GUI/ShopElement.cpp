#include "ShopElement.h"

#include <utility>


ShopElement::ShopElement(ElementType weaponType, sf::Text weaponText, sf::Text goldText) : GUI_Element({100.f, 100.f}),
                                                                                           weapon_type(weaponType),
                                                                                           weapon_name(std::move(weaponText)),
                                                                                           gold_text(std::move(goldText)) {
    background.setSize({100.f, 100.f});
    background.setFillColor(sf::Color{128, 128, 128, 64});

    background.setPosition(10.f, 10.f);

    weapon_name.setCharacterSize(15);
    gold_text.setCharacterSize(13);

    weapon_name.setPosition(20.f, 50.f);
    gold_text.setPosition(20.f, 80.f);
}

void ShopElement::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(background, states);
    target.draw(weapon_name, states);
    target.draw(gold_text, states);
}

std::shared_ptr<WeaponGUI> ShopElement::get() const{
    return std::make_shared<WeaponGUI>(weapon_type);
}