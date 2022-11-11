#pragma once
#include "../baseHeaders.h"

class MenuOption: public sf::Text {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    size_t id;
    float width = 0.f;
    float height = 0.f;

public:

    //make static size_t num for id's?
    MenuOption():id(0) {};
    ~MenuOption() override = default;

//    sf::Texture getTexture() const;
//    void setTexture(sf::Texture);
//
//    sf::Sprite getSprite() const;
//    void setSprite(sf::Sprite);
//
//    float getWidth() const;
//    void setWidth(float);
//
//    float getHeight() const;
//    void setHeight(float);

    friend class MainMenu;
    friend class LevelMenu;
};
