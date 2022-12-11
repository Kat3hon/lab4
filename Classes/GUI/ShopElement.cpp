#include "ShopElement.h"

#include <utility>


Shop::ShopItem(TowerType towerType, sf::Text towerName, sf::Text goldText) : UIElement({100.f, 100.f}),
                                                                                 m_towerType(towerType),
                                                                                 m_towerName(std::move(towerName)),
                                                                                 m_goldText(std::move(goldText)) {
    m_background.setSize({100.f, 100.f});
    m_background.setFillColor(sf::Color{128, 128, 128, 64});

    m_background.setPosition(10.f, 10.f);

    m_towerName.setCharacterSize(15);
    m_goldText.setCharacterSize(13);

    m_towerName.setPosition(20.f, 50.f);
    m_goldText.setPosition(20.f, 80.f);
}

Shop::Shop() {

}


std::shared_ptr<Tower> Shop::getTower() {
    return std::make_shared<Tower>(m_towerType);
}

void Shop::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(m_background, states);
    target.draw(m_towerName, states);
    target.draw(m_goldText, states);
}