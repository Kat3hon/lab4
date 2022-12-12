#include "GUI_Element.h"
#include "../GameLogic/Tower.h"

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// An element of a in-game shop.
class ShopElement: public GUI_Element, public sf::Drawable {

    /// Name of a tower to buy.
    sf::Text tower_name;

    /// Price of a tower.
    sf::Text gold_text;

    /// Type of tower.
    TowerType tower_type;

    /// Tower texture.
    sf::RectangleShape background;

public:

    /// Needs for explicit constructor in GameMenu.
    ShopElement() = default;

    /// Sets a shop element characteristics to render.
    ShopElement(TowerType towerType, sf::Text towerText, sf::Text goldText);

    /// Draws a shop element
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /// Gets a shop element
    std::shared_ptr<Tower> getElement(); //Maybe const?
};