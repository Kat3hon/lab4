//
// Created by kklim on 02.11.2022.
//
#pragma once
#include "..\IGame\IGame.h"
#include "..\DefaultFont\DefaultFont.h"
#include "menuParticleSystem.hpp"
#include "..\Button\Button.h"
#include <thread>

#define MAINMENU

class MainMenu: public IGame, private Font {
private:
    std::thread loadingThread;
    sf::Text title;
    menuParticleSystem particleSystem;

    std::vector <Button> buttons;
    void handleButtons();

    int currentButton;
    void followFunc(int index);

public:
    MainMenu();
    ~MainMenu();

    void update();
    void draw(sf::RenderWindow &window) const;
};
