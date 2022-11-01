//
// Created by kklim on 02.11.2022.
//
#pragma once
#include "..\Base\Base.h"

enum Type {SMALL, MEDIUM, LARGE};

class Button: public sf::Text {
private:
    bool isBoosted;

public:
    Button(Type type = MEDIUM, sf::Vector2f position = sf::Vector2f(0.f,0.f), std::string caption = "Captio");
    ~Button() {};
    Type size;

    void increase();
    void decrease();
    bool isMouseOn(sf::Vector2f mousePosition);

    bool isIncreased();
    bool isClickOn(sf::Vector2f mousePosition);
};
