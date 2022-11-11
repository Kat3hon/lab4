#pragma once
#include "SFML/Graphics.hpp"
#include <windows.h>
#include <sstream>

using namespace sf;

class FPS: public sf::Drawable {
private:
    size_t fps;
    sf::Time fpsTimer;
    static const sf::Time second;
    sf::Text fpsText;
    sf::Font fpsFont;

public:
    FPS();
    ~FPS() override = default;

    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    void countTime(sf::Time &dTimer);

    FPS & operator++();
};
