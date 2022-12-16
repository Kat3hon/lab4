#include "Level.h"

using namespace tinyxml2;

// On Windows, backslash '\\' is directory separator in paths
// On UNIX paths separated with slash '/'.
//#if defined(_WIN32)
//const char DIR_SEPARATOR = '\\';
//#else
//const char DIR_SEPARATOR = '/';
//#endif

using namespace sf;

const char DIR_SEPARATOR = '/';

// Returns parent directory of given path;
std::string getParentDirectory(const std::string &filepath) {
    const size_t slashPos = filepath.find_last_of('/');
    std::string parentDir;
    if (slashPos != std::string::npos)
        parentDir = filepath.substr(0, slashPos);
    return parentDir;
}

// Joins two path fragments, e.g. directory path and filename
std::string joinPaths(const std::string &path, const std::string &subpath) {
    if (path.empty())
        return subpath;
    if (subpath.empty())
        return path;
    return path + DIR_SEPARATOR + subpath;
}

// Parses hex-encoded RGB like "6d9fb9"
sf::Color parseColor(const std::string &hexRGB) {
    char *pEnd = nullptr;
    const long hexValue = strtol(hexRGB.c_str(), &pEnd, 16);
    if (*pEnd != '\0')
        throw std::runtime_error(hexRGB + " is not valid hex-encoded RGB color");

    const auto red = uint8_t((hexValue >> 16) % 256);
    const auto green = uint8_t((hexValue >> 8) % 256);
    const auto blue = uint8_t(hexValue % 256);

    return {red, green, blue};
}

bool Level::loadFromFile(const std::string &filepath) {
    XMLDocument levelFile;

    // Load XML into XMLDocument
    if (levelFile.LoadFile(filepath.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Loading level \"" + filepath + "\" failed.");

    // Element <Vector> should be root in TMX format.
    XMLElement *map = levelFile.FirstChildElement("Vector");
    if (map == nullptr)
        throw std::runtime_error("<Vector> element not found");

    // Vector element example:
    //   <Vector version="1.0" orientation="orthogonal"
    //    width="10" height="10" tilewidth="34" tileheight="34">
    width = std::stoi(map->Attribute("width"));
    height = std::stoi(map->Attribute("height"));
    tile_width = std::stoi(map->Attribute("tilewidth"));
    tile_height = std::stoi(map->Attribute("tileheight"));

    // Retrieve tileset description and the first tile GID (Group Identifier).
    XMLElement *tilesetElement = map->FirstChildElement("tileset");
    first_tileID = std::stoi(tilesetElement->Attribute("firstgid"));

    // <image> contains tileset texture
    XMLElement *image = tilesetElement->FirstChildElement("image");
    const std::string imageFilename = image->Attribute("source");
    const std::string imagePath = joinPaths(getParentDirectory(filepath), imageFilename);

    sf::Color matteColor = sf::Color(0, 0, 0, 0);
    if (image->Attribute("trans") != nullptr)
        matteColor = parseColor(image->Attribute("trans"));

    sf::Image img;
    if (!img.loadFromFile(imagePath)) {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    // Set tileset matte color, used to composite transparent image on
    // background filled with matte color.
    img.createMaskFromColor(matteColor);
    // Load texture from file.
    tileset_texture.loadFromImage(img);
    // Keep texture sharp when resized.
    tileset_texture.setSmooth(false);

    // Retrieve amount of rows and columns in tileset.
    const int columns = tileset_texture.getSize().x / tile_width;
    const int rows = tileset_texture.getSize().y / tile_height;

    // Collect texture rects list.
    // Each texture rect is subimage in tileset image, i.e. single tile image.
    std::vector<sf::IntRect> subRects;
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++) {
            sf::IntRect rect;
            rect.top = y * tile_height;
            rect.height = tile_height;
            rect.left = x * tile_width;
            rect.width = tile_width;
            subRects.push_back(rect);
        }


    ////////////////////////////////////////////////////////////////////////////
    /// Parse tile layers
    ///
    XMLElement *layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        Layer layer;
        // Copy transparency if it set in XML or make layer opaque (255).
        if (layerElement->Attribute("opacity") != nullptr) {
            float opacity = parseFloat(layerElement->Attribute("opacity"));
            layer.opacity = sf::Uint8(255 * opacity);
        }
        else layer.opacity = 255;

        // <data> contains multiple tiles_sprites description.
        XMLElement *layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == nullptr)
            std::cout << "Bad Vector. No layer information found." << std::endl;

        // <tile> contains single tile description.
        XMLElement *tileElement = layerDataElement->FirstChildElement("tile");
        if (tileElement == nullptr) {
            std::cout << "Bad Vector. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;
        while (tileElement) {
            int tileGID = -1;
            if (tileElement->Attribute("gid") != nullptr)
                tileGID = std::stoi(tileElement->Attribute("gid"));
            const int subRectToUse = tileGID - first_tileID;
            // Figure out texture rect for each tile.
            if (subRectToUse >= 0) {
                sf::Sprite sprite;
                sprite.setTexture(tileset_texture);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(static_cast<float>(x * tile_width), static_cast<float>(y * tile_height));
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles_sprites.push_back(sprite);
            }
            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width) {
                x = 0;
                y++;
                if (y >= height) {
                    y = 0;
                }
            }
        }
        layers.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Collecting objects list.
    ///

    // If there are object layers.
    if (map->FirstChildElement("objectgroup") != nullptr) {
        XMLElement *objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            // Enter into <object> node
            XMLElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement) {
                // Collecting object properties - type, name, position, etc.
                std::string objectType;
                if (objectElement->Attribute("type") != nullptr) {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != nullptr) {
                    objectName = objectElement->Attribute("name");
                }
                float x = std::stof(objectElement->Attribute("x"));
                float y = std::stof(objectElement->Attribute("y"));
                float width_v = 0;
                float height_v = 0;

                sf::Sprite sprite;
                sprite.setTexture(tileset_texture);
                sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != nullptr) {
                    width_v = std::stof(objectElement->Attribute("width"));
                    height_v = std::stof(objectElement->Attribute("height"));
                }
                else {
                    const size_t index = std::stoi(objectElement->Attribute("gid")) - first_tileID;
                    width_v = static_cast<float>(subRects[index].width);
                    height_v = static_cast<float>(subRects[index].height);
                    sprite.setTextureRect(subRects[index]);
                    sprite.setOrigin(0, height_v);
                }

                // Define object
                GameObject object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::FloatRect objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height_v;
                objectRect.width = width_v;
                object.rect = objectRect;

                // Read object properties
                XMLElement *properties = objectElement->FirstChildElement("properties");
                if (properties != nullptr) {
                    XMLElement *prop = properties->FirstChildElement("property");
                    if (prop != nullptr) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                // Add object to list
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else std::cout << "No object layers found..." << std::endl;
    return true;
}

GameObject Level::getFirstObject(const std::string &name) const {
    // Only first object with given name
    for (const auto & object : objects)
        if (object.name == name)
            return object;
    throw std::runtime_error("GameObject with name " + name + " was not found");
}

std::vector<GameObject> Level::getAllObjects(const std::string &name) const {
    // All objects with given name
    std::vector<GameObject> vec;
    for (const auto & object : objects)
        if (object.name == name)
            vec.push_back(object);
    return vec;
}

sf::Vector2i Level::getTileSize() const {
    return {tile_width, tile_height};
}

float Level::getTilemapWidth() const {
    return static_cast<float>(tile_width * width);
}

float Level::getTilemapHeight() const {
    return static_cast<float>(tile_height * height);
}

sf::Vector2f Level::getTilemapSize() const {
    return {getTilemapWidth(), getTilemapHeight()};
}

void Level::draw(sf::RenderTarget &target) const {
    const sf::FloatRect viewportRect = target.getView().getViewport();

    // draw all tiles_sprites (and don't draw objects)
    for (const auto &layer : layers) {
        for (const auto &tile : layer.tiles_sprites) {
            if (viewportRect.intersects(tile.getLocalBounds())) {
                target.draw(tile);
            }
        }
    }
}

void Level::constructGraph() {
    for (const auto &layer : layers) {
        for (const auto &tile : layer.tiles_sprites) {
            for (const auto &object: objects) {
                if (object.rect.intersects(Rect<float>(tile.getTextureRect())) && object.name == "path") {
                    std::cout << tile.getTextureRect().top << std::endl;
                }
            }
        }
    }
}

//void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//    states.transform *= getTransform();
//    states.texture = &m_tileset;
//
//    target.draw(m_vertices, states);
//}
//
//Tile::Ptr Level::getTileFromMouse(sf::Vector2<float> vector) const {
//    sf::Vector2<float> position = getPosition();
//    const float xRelative = vector.x - position.x;
//    const float yRelative = vector.y - position.y;
//
//    // minus 1 here. Because if the max size is lets say 650
//    // 650 will be resolved to column 10, and that does not exist.
//    float xMax = getTilemapWidth() - 1;
//    float yMax = getTilemapHeight() - 1;
//
//    if (xRelative < 0 || yRelative < 0) return nullptr;
//    if (xRelative > xMax || yRelative > yMax) return nullptr;
//
//    auto col = static_cast<unsigned int>(std::floor(xRelative / TILE_SIZE));
//    auto row = static_cast<unsigned int>(std::floor(yRelative / TILE_SIZE));
//
//    return m_tiles[col][row];
//}
//
//sf::Vector2<float> Level::getTileWindowPosition(const Tile::Ptr &tile) const {
//    // This function is used, to calculate to find the position
//    // on where to position the enemy and/or weapons.
//    sf::Vector2<float> gridPosition = getPosition();
//
//    const auto yRelative = static_cast<float>(tile->getY() * TILE_SIZE);
//    const auto xRelative = static_cast<float>(tile->getX() * TILE_SIZE);
//
//    return sf::Vector2f{gridPosition.x + xRelative, gridPosition.y + yRelative};
//}
//
//sf::Vector2<int> Level::getEnemySpawnTileCoordinate() const {
//    if (m_enemyPathingPoints.empty()) {
//        throw std::logic_error("No enemy spawn point set");
//    }
//
//    return *m_enemyPathingPoints.begin();
//}
//
//sf::Vector2<int> Level::getEnemyTargetTileCoordinate() const {
//    if (m_enemyPathingPoints.empty()) {
//        throw std::logic_error("No enemy target point set");
//    }
//
//    return *m_enemyPathingPoints.end();
//}
//
//sf::Vector2<int> Level::getEnemyPathTileCoordinate(unsigned int pathIndex) const {
//
//    if(pathIndex >= m_enemyPathingPoints.size()) {
//        return m_enemyPathingPoints[m_enemyPathingPoints.size() - 1];
//    }
//
//    return m_enemyPathingPoints[pathIndex];
//}
//
//Tile::Ptr Level::getTileFromCoordinate(sf::Vector2<int> vector) const {
//
//    if (vector.x >= m_tiles.size() || vector.y >= m_tiles[vector.x].size()) {
//        return nullptr;
//    }
//
//    return m_tiles[vector.x][vector.y];
//}
//
//sf::Vector2<float> Level::getTileWindowPositionFromTileCoordinate(sf::Vector2<int> coordinate) const {
//    const Tile::Ptr tile = getTileFromCoordinate(coordinate);
//
//    if (tile == nullptr) {
//        return sf::Vector2<float>{0, 0};
//    }
//
//    return getTileWindowPosition(tile);
//}