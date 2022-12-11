#include "GUI_Element.h"

#include "exception/cantBeDrawnException.hpp"

GUI_Element::GUI_Element(sf::Vector2f vector) {
    m_vector = vector;
}

void GUI_Element::bindClick(const GUI_Element::ClickHandler &handler) {
    m_clickHandler = handler;
}

void GUI_Element::bindHover(const GUI_Element::HoverHandler &handler) {
    m_hoverHandler = handler;
}

void GUI_Element::onClick() {
    if (!m_clickHandler) return;

    m_clickHandler();
}

void GUI_Element::onHover() {
    if (m_hoverHandler) return;

    m_hoverHandler();
}

float GUI_Element::getWidth() {
    return m_vector.x;
}

float GUI_Element::getHeight() {
    return m_vector.y;
}

void GUI_Element::setWidth(float width) {
    m_vector.x = width;
}

void GUI_Element::setHeight(float height) {
    m_vector.y = height;
}

void GUI_Element::update() {

}
