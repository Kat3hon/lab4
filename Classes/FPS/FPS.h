#pragma once
#include "..\Base\Base.h"

class FPS: public sf::Drawable {
private:
    int fps;
    sf::Time timer;
    const sf::Time second = sf::seconds(1.f);
    sf::Text fpsText;
    sf::Font font;

public:
    FPS();
    ~FPS();

    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    void countTime(sf::Time &gameTimer);

    FPS & operator++();
};
