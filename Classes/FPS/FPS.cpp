//
// Created by kklim on 02.11.2022.
//

#include "FPS.h"

FPS::FPS() {
    if (!font.loadFromFile("Fonts/Comfortaa.ttf"))
        MessageBox(0, "Can not load Comfortaa.ttf", 0, 0);

    fps = 0;
    timer = sf::Time::Zero;

    fpsText.setFont(font);
    fpsText.setCharacterSize(30);
    fpsText.setColor(sf::Color(200, 200, 220));
    fpsText.setString("fps = ");
}

FPS::~FPS(){}

void FPS::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(fpsText);
}

void FPS::countTime(sf::Time & gameTimer) {
    timer += gameTimer;

    if (timer >= second) {
        fpsText.setString("fps = " + intToString(fps));
        fps = 0;
        timer = sf::Time::Zero;
    }
}

FPS & FPS::operator++() {
    fps++;
    return *this;
}
