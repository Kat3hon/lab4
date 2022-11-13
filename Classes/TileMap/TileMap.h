#pragma once
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include "../baseHeaders.h"
#include "..\..\tinyxml\tinyxml2.h"
#include "..\ObjectXML\ObjectXML.h"

class TileMap : public sf::Drawable {
private:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    std::unique_ptr<sf::Texture> texture;
    std::vector<sf::VertexArray> tile_layers;
    std::vector<ObjectXML> objects;

public:
    ~TileMap() = default;

    bool load(const std::string& tmx_file_path);

    ObjectXML getObject(const std::string& name);
    std::vector<ObjectXML> getObjectsByName(const std::string& name);
    std::vector<ObjectXML> getObjectsByType(const std::string& type);
    std::vector<ObjectXML>& getAllObjects();
};
