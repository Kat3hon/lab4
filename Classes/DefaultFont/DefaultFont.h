//
// Created by kklim on 02.11.2022.
//
#pragma once
#include "..\Base\Base.h"

class Font {
protected:
    sf::Font font;
public:
    Font() {
        if (!font.loadFromFile("Fonts/Comfortaa.ttf")) return;
    }
};
