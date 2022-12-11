#include "GameObject.h"

#include <SFML/Graphics/Rect.hpp>

GameObject::GameObject() {

}

void GameObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

bool GameObject::collidesWith(GameObject *gameObject) {
    sf::Rect<float> currentRect(getPosition(), {
            m_width,
            m_height
    });

    sf::Rect<float> targetRect(gameObject->getPosition(), {
            gameObject->getWidth(),
            gameObject->getHeight()
    });

    return currentRect.intersects(targetRect);
}

void GameObject::setHeight(float height) {
    m_height = height;
}

void GameObject::setWidth(float width) {
    m_width = width;
}

float GameObject::getHeight() {
    return m_height;
}

float GameObject::getWidth() {
    return m_width;
}
