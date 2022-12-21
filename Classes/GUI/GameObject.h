#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

// In TMX maps, an object is an area on the map that has a name, type, boundaries,
// a set of custom properties (in key-value format) and texture coordinates.
// Texture coordinates allow you to associate a sprite with an object
// that uses the main texture of the map as a data source.

class GameObject: public sf::Transformable, public sf::Drawable{


public:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    int getPropertyInt(const std::string &propertyName);

    float getPropertyFloat(const std::string &propertyName);

    std::string getPropertyString(const std::string &propertyName);

    void moveBy(const sf::Vector2f &movement);

    void moveTo(const sf::Vector2f &position);

    sf::Rect<float> getRect() const;

    bool collidesWith(GameObject *gameObject);

    std::string name;
    std::map<std::string, std::string> properties;
    sf::Rect<float> rect;
    sf::Sprite sprite;
    std::string type;
};

float parseFloat(const std::string &str);
