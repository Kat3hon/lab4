#include "GameObject.h"
#include <SFML/Graphics/Rect.hpp>

void GameObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}

bool GameObject::collidesWith(GameObject *gameObject) {
    return this->getRect().intersects(gameObject->getRect());
}

float parseFloat(const std::string &str) {
    char *pEnd = nullptr;
    const float value = strtof(str.c_str(), &pEnd);
    if (*pEnd != '\0')
        throw std::runtime_error("'" + str + "' is not a float number");
    return value;
}

int GameObject::getPropertyInt(const std::string &propertyName) {
    return std::stoi(properties[propertyName]);
}

float GameObject::getPropertyFloat(const std::string &propertyName) {
    return parseFloat(properties[propertyName]);
}

std::string GameObject::getPropertyString(const std::string &propertyName) {
    return properties[propertyName];
}

void GameObject::moveBy(const sf::Vector2f &movement) {
    rect.left += movement.x;
    rect.top += movement.y;
    sprite.move(movement);
}

void GameObject::moveTo(const sf::Vector2f &position) {
    rect.left = position.x;
    rect.top = position.y;
    sprite.setPosition(position);
}

sf::Rect<float> GameObject::getRect() const {
    return rect;
}

