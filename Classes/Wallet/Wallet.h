#pragma once
#include "../baseHeaders.h"
#include "../AnimationManager/AnimationManager.h"
#include <sstream>

class Wallet {
private:
    int gold; //текущее золото
    sf::Text goldText;
    sf::Sprite coin;
    sf::Texture texture;
    AnimationManager anim;
    sf::Font font;

public:
    Wallet();
    ~Wallet() = default;
    void draw(sf::RenderWindow & window);
    int getGold() const;
    bool isAfford(int amount) const; //узнать можно ли купить за текущее золото
    void pay(int amount); //заплатить за что-то
    void setPosition(const sf::Vector2f position);
    void deposit(int amount);
    void setFont(sf::Font new_font);
    void setGoldText();

    sf::Vector2f getSize();
};
