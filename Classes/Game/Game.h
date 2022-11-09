#pragma once

class Game {
private:
    //static Game *instance;

    sf::RenderWindow window;
    sf::Event event;
    sf::Font font;
    sf::Image icon;

    //std::unique_ptr <IGame> gameController;

    sf::Time time;
    static const sf::Time frameTime;
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
    sf::RenderWindow & getWindow();
    sf::Font *getFont();
    sf::Time getTimer() const;
    void setController(std::unique_ptr <IGame> newController);
    void exit();
    sf::Music * getMusic();
    //void boost();
};

