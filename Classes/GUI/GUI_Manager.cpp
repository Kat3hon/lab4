#include "GUI_Manager.h"

#include <iostream>

void GUI_Manager::registerElement(GUI_Element *element) {
    m_elements.push_back(element);
}

void GUI_Manager::resolveClick(sf::Vector2i position) {

    if (position.x == 0 && position.y == 0) return; // We have to do this, window::isOpen does not work?

    // we use a reverse iterator here, because it could be that at some point
    // ui elements need to be rendered on top of each other
    // e.g. if there's an overlay. you would still be clicking on
    // elements underneath the overlay, we don't want that.
    for (auto it = m_elements.rbegin(); it != m_elements.rend(); it++) {

        GUI_Element *element = *it;

        // Since these are not shapes, we have to implement our own 'contains' method.
        const float x = element->getPosition().x;
        const float y = element->getPosition().y;

        const float width = element->getWidth();
        const float height = element->getHeight();

        if (position.x >= x && position.x <= x + width) {
            if (position.y >= y && position.y <= y + height) {
                // we are not going to click on underlying elements.
                return element->onClick();
            }
        }
    }
}