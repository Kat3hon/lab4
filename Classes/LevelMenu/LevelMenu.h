#pragma once

#include "..\baseHeaders.h"
#include "..\MainMenu\MainMenu.h"
#include "..\MainGame\MainGame.h"
#include <vector>

class LevelMenu: public IController {
private:
    //sf::Thread loadingThread;
    std::vector <MenuOption> option;
    size_t buttonPressed;

public:
    LevelMenu();
    ~LevelMenu() override = default;

    void update() override;
    void draw(sf::RenderWindow &window) override;

};

