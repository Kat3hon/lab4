//
// Created by kklim on 01.11.2022.
//
#pragma once
#include "..\Base\Base.h"
#include "..\IGame\IGame.h"
#include "..\ButtonSwitcher\ButtonSwithcer.h"
#include "..\FPS\FPS.h"
#define mainLoop

class Game
{
private:
    static Game *instance;

    sf::RenderWindow window;
    sf::Event evnt;
    sf::Font font;
    sf::Image icon;

    std::unique_ptr <IGame> gameController;

    sf::Time accumulator;
    const sf::Time frameTime = sf::seconds(1.f / 120.f);
    sf::Clock clock;

    sf::Time timer;
    sf::Clock clocker;

    FPS fps;
    sf::Music music;
    void loadFont();


public:
    Game();
    ~Game();

    void run();

    static Game * getInstance();
    sf::RenderWindow & getWindow() const;
    sf::Font *getFont() const;
    sf::Time getTimer() const;
    void setController(std::unique_ptr <IGame> newController);
    void exit();
    sf::Music * getMusic() const;
    void hurryUpTime();
};