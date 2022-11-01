//
// Created by kklim on 02.11.2022.
//
#include "ButtonSwitcher.h"
#include "..\Base\Base.h"

bool ButtonSwitcher::isButtonActive = false;
std::map<sf::Keyboard::Key, bool> ButtonSwitcher::buttons = std::map<sf::Keyboard::Key, bool>();

ButtonSwitcher::ButtonSwitcher() {
    isButtonActive = false;
}

ButtonSwitcher::~ButtonSwitcher() {}

void ButtonSwitcher::update() {
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(!isButtonActive))
        isButtonActive = true;
    else if ((!sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(isButtonActive))
        isButtonActive = false;

    std::map<sf::Keyboard::Key, bool>::iterator itr = buttons.begin(), end = buttons.end();

    for (itr; itr != end; itr++) {
        if (sf::Keyboard::isKeyPressed(itr->first) && (!itr->second))
            itr->second = true;
        else if ((!sf::Keyboard::isKeyPressed(itr->first)) && (itr->second))
            itr->second = false;
    }
}

bool ButtonSwitcher::canClick() {
    return !isButtonActive;
}

bool ButtonSwitcher::canClickKey(sf::Keyboard::Key key) {
    std::map<sf::Keyboard::Key, bool>::iterator itr = buttons.find(key);
    if (itr == buttons.end()) {
        buttons[key] = true;
        return true;
    }

    if (itr->second)
        return false;
    else {
        itr->second = true;
        return true;
    }
}

