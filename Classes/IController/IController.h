#pragma once
#include "..\baseHeaders.h"

class IController {
public:
    virtual ~IController() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};
