//
// Created by kklim on 02.11.2022.
//
#pragma once
#include "..\Base\Base.h"

class IGame {
public:
    virtual ~gameCtrl() {};
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};