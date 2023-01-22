#include "GameObject.h"


bool GameObject::collidesWith(GameObject *gameObject) {
    sf::Rect<float> currentRect(getPosition(), {
            width,
            height
    });

    sf::Rect<float> targetRect(gameObject->getPosition(), {
            gameObject->getWidth(),
            gameObject->getHeight()
    });

    return currentRect.intersects(targetRect);
}

void GameObject::setHeight(float height_v) {
    height = height_v;
}

void GameObject::setWidth(float width_v) {
    width = width_v;
}

float GameObject::getHeight() const {
    return height;
}

float GameObject::getWidth() const {
    return width;
}