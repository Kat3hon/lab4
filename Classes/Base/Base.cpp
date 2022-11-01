//
// Created by kklim on 02.11.2022.
//
#include "Base.h"
#include <sstream>

std::string intToString(int number) {
    std::stringstream ss;
    ss << number;
    return ss.str();
}

std::string floatToString(float number) {
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

sf::Vector2f getMiddlePosition(sf::FloatRect pointObject, sf::FloatRect positioningObject) {
    sf::Vector2f middlePos;
    middlePos.x = pointObject.left + pointObject.width / 2 - positioningObject.width / 2;
    middlePos.y = pointObject.top + pointObject.height / 2 - positioningObject.height / 2;
    return middlePos;
}

sf::Vector2f getMidlePosition(sf::Vector2f pointPos, sf::FloatRect positioningObject) {
    sf::Vector2f middlePos;
    middlePos.x = pointPos.x - positioningObject.width / 2;
    middlePos.y = pointPos.y - positioningObject.height / 2;
    return middlePos;
}

sf::Vector2f getMousePos() {
    return sf::Vector2f(sf::Mouse::getPosition(Game::getInstance()->getWindow()));
}

bool objectClicked(sf::FloatRect object) {
    if ((object.contains(getMousePos())) && (ButtonSwitcher::canClick()) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
        return true;

    return false;
}

bool isPositive(float number) {
    return number > 0;
}

bool isNegative(float number) {
    return number < 0;
}
