#pragma once

#include "../baseHeaders.h"
#include "../FPS/FPS.h"
#include "../IController/IController.h"
#include "../MainMenu/MainMenu.h"

class Game {
private:

    static Game* instance;

    sf::Event event;
    sf::Image icon;

    sf::Time time;
    sf::Clock clock;
    static const sf::Time frameTime;

    FPS fps;

    std::unique_ptr<IController> currentController;

    //can be made static, so need to change constructors MainMenu, LevelMenu
    sf::Music music;
    sf::Font font;
    sf::RenderWindow window;

public:
    friend class MainMenu;
    friend class LevelMenu;
    friend class MainGame;

    void setController(std::unique_ptr <IController> newController);

    Game();
    ~Game();

    void run();
    void exit();

    //void boost();

    //IController classes must use music, font and window
    //Also they use exit and setMenu()
    //How to organize their connections?
    //Friend methods?

    sf::Music* getMusicPtr() { return &music; }
    sf::Window* getWindowPtr() { return &window; }
    sf::Font getFont() { return font; }
};