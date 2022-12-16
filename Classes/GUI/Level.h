#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Storage/tinyxml/tinyxml2.h"

/// Reads map from XML file

// In TMX maps, an object is an area on the map that has a name, type, boundaries,
// a set of custom properties (in key-value format) and texture coordinates.
// Texture coordinates allow you to associate a sprite with an object
// that uses the main texture of the map as a data source.
struct Object {
    int getPropertyInt(const std::string &propertyName);

    float getPropertyFloat(const std::string &propertyName);

    std::string getPropertyString(const std::string &propertyName);

    void moveBy(const sf::Vector2f &movement);
    void moveTo(const sf::Vector2f &position);

    std::string name;
    std::string type;
    sf::FloatRect rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

/// In TMX maps, a layer is a set of tiles (sprites) that make up the landscape of the map.
struct Layer {
    sf::Uint8 opacity = 0;
    std::vector<sf::Sprite> tiles;
};

class Level {

    int width = 0;

    int height = 0;

    int tile_width = 0;

    int tile_height = 0;

    int first_tileID = 0;

    sf::Texture tileset_texture;

    std::vector<Object> objects;

    std::vector<Layer> layers;

public:

    bool loadFromFile(const std::string &filepath);

    Object getFirstObject(const std::string &name) const;

    std::vector<Object> getAllObjects(const std::string &name) const;

    sf::Vector2i getTileSize() const;

    float getTilemapWidth() const;

    float getTilemapHeight() const;

    sf::Vector2f getTilemapSize() const;

    /// Renders all layers, but not objects.
    void draw(sf::RenderTarget & target) const;
};