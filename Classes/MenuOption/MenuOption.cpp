#include "MenuOption.h"

//MenuOption::MenuOption(const std::string& filename, float width, float height, size_t size, sf::Texture texture) {
//    sprite.setTexture(texture);
//    width = width;
//    height = height;
//    sprite.setPosition(width, height);
//    id = size;
//}

sf::Sprite MenuOption::getSprite() const {
    return sprite;
}

float MenuOption::getWidth() const {
    return width;
}

float MenuOption::getHeight() const {
    return height;
}

size_t MenuOption::getID() const {
    return id;
}

void MenuOption::setColor(sf::Color color) {
    sprite.setColor(color);
}