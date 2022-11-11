#include "FPS.h"

const sf::Time FPS::second = sf::seconds(1.f);

FPS::FPS():fps(0), fpsTimer(sf::Time::Zero) {
    if (!fpsFont.loadFromFile("../Storage/Fonts/Comfortaa.ttf"))
        MessageBox(nullptr, "Can not load Comfortaa.ttf", "Error!", MB_OK);

    fpsText.setFont(fpsFont);
    fpsText.setCharacterSize(30);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setString("fps = ");
}

void FPS::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(fpsText);
}

void FPS::countTime(sf::Time & dTime) {
    fpsTimer += dTime;

    if (fpsTimer >= second) {
        std::stringstream tmpStream;
        tmpStream << fps;
        std::string fpsString = tmpStream.str();
        fpsText.setString("fps = " + fpsString);
        fps = 0;
        fpsTimer = sf::Time::Zero;
    }
}

FPS& FPS::operator++() {
    fps++;
    return *this;
}
