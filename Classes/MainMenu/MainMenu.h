#pragma once

#include "..\baseHeaders.h"
#include "..\IController\IController.h"
#include "..\MenuOption\MenuOption.h"
#include "..\LevelMenu\LevelMenu.h"
#include "..\Game\Game.h"

class MainMenu: public IController {
private:
    std::vector <MenuOption> option;
    size_t buttonPressed;

public:
    MainMenu();
    ~MainMenu() override = default;

    void update() override;
    void draw(sf::RenderWindow &window) override;

};
