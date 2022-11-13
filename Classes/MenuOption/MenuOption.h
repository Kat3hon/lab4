#pragma once
#include "../baseHeaders.h"

class MenuOption {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    size_t id = 0;
    float width = 0.f;
    float height = 0.f;

public:
    MenuOption() = default;
    ~MenuOption() = default;

    sf::Sprite getSprite() const;
    float getWidth() const;
    float getHeight() const;
    size_t getID() const;

    void setColor(sf::Color color);

    friend class MainMenu;
    friend class LevelMenu;

};
