#include "GUI_Element.h"
#include "../../game/tower/tower.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Shop : public GUI_Element, public sf::Drawable {
public:
    Shop(TowerType towerType, sf::Text towerText, sf::Text goldText);
    Shop();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::shared_ptr<Tower> getTower();

private:
    sf::Text m_towerName;

    sf::Text m_goldText;

    TowerType m_towerType;

    sf::RectangleShape m_background;
};