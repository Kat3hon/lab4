#include "Level.h"

using namespace tinyxml2;

// On Windows, backslash '\\' is directory separator in paths
// On UNIX paths separated with slash '/'.
//#if defined(_WIN32)
//const char DIR_SEPARATOR = '\\';
//#else
//const char DIR_SEPARATOR = '/';
//#endif

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
    //  background filled with matte color.
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

        // <data> contains multiple tiles description.
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

                layer.tiles.push_back(sprite);
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

    // draw all tiles (and don't draw objects)
    for (const auto &layer : layers) {
        for (const auto &tile : layer.tiles) {
            if (viewportRect.intersects(tile.getLocalBounds())) {
                target.draw(tile);
            }
        }
    }
}