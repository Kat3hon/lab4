//
// Created by kklim on 02.11.2022.
//
#pragma once
#include <iostream>
#include "../Base/Base.h"

class ButtonSwitcher {
private:
    static bool isButtonActive;
    static std::map<sf::Keyboard::Key, bool> buttons;
    int INt;

public:
    ButtonSwitcher();
    ~ButtonSwitcher();
    static void update();
    static bool canClick();
    static bool canClickKey(sf::Keyboard::Key key);
};
