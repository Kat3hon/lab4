#pragma once

#include "../GameLogic/GameObject.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "tinyxml/tinyxml2.h"

/// Reads map from XML file

// In TMX maps, an object is an area on the map that has a name, type, boundaries,
// a set of custom properties (in key-value format) and texture coordinates.
// Texture coordinates allow you to associate a sprite with an object
// that uses the main texture of the map as a data source.

/// In TMX maps, a layer is a set of tiles (sprites) that make up the landscape of the map.
struct Layer {
    sf::Uint8 opacity = 0;
    std::vector<sf::Sprite> tiles;
};

class Level {

    /// Width of level in tiles.
    int width = 0;

    /// Height of level in tiles.
    int height = 0;

    int tile_width = 0;

    int tile_height = 0;

    int first_tileID = 0;

    sf::Texture tileset_texture;

    /// Game objects on that level, that can be moved.
    std::vector<GameObject> objects;

    /// Layers to render.
    std::vector<Layer> layers;

public:

    /// Sets all fields from file.
    bool loadFromFile(const std::string &filepath);

    /// Gets first object with that name.
    GameObject getFirstObject(const std::string &name) const;

    /// Gets vector of all objects with that name.
    std::vector<GameObject> getAllObjects(const std::string &name) const;

    /// Gets tile size.
    sf::Vector2i getTileSize() const;

    /// Gets width of a map.
    float getTilemapWidth() const;

    /// Gets height of a map.
    float getTilemapHeight() const;

    /// Gets size of a map.
    sf::Vector2f getTilemapSize() const;

    /// Renders all layers, but not objects.
    void draw(sf::RenderTarget & target) const;
};