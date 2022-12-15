#include "ShopElement.h"

#include <utility>


ShopElement::ShopElement(TowerType towerType, sf::Text towerName, sf::Text goldText) : GUI_Element({100.f, 100.f}),
                                                                                 tower_type(towerType),
                                                                                 tower_name(std::move(towerName)),
                                                                                 gold_text(std::move(goldText)) {
    background.setSize({100.f, 100.f});
    background.setFillColor(sf::Color{128, 128, 128, 64});

    background.setPosition(10.f, 10.f);

    tower_name.setCharacterSize(15);
    gold_text.setCharacterSize(13);

    tower_name.setPosition(20.f, 50.f);
    gold_text.setPosition(20.f, 80.f);
}

void ShopElement::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(background, states);
    target.draw(tower_name, states);
    target.draw(gold_text, states);
}

std::shared_ptr<Tower> ShopElement::get() const{
    return std::make_shared<Tower>(tower_type);
}