//
// Created by kklim on 01.11.2022.
//
#include "Game.h"
#include "..\MainMenu\MainMenu.h"

const sf::Time Game::frameTime = sf::seconds(1.f / 120.f);

Game::Game():window(sf::VideoMode(WIDTH, HEIGHT), "Tower Defense Game") {

    //set main menu music
    if (!music.openFromFile("Music/mainMenuTheme.wav")) {
        MessageBox(0, "Can not open mainMenuTheme.wav", 0, 0);
        exit();
    }
    music.play();
    music.setLoop(true);

    //set icon
    if (!icon.loadFromFile("Textures/icon.png")) {
        MessageBox(0, "Can not open icon.png", 0, 0);
        exit();
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //set font
    if (!font.loadFromFile("Fonts/Comfortaa.ttf"))
        MessageBox(0, "Can not load a font Comfortaa", 0, 0);

    gameController = std::make_unique<MainMenu>();


    time = sf::Time::Zero;
    clock.restart();
}

Game::~Game() {
    instance = nullptr;
}

void Game::run() {
    sf::Time deltaTime = sf::Time::Zero;
    sf::Clock deltaClock;

    while (window.isOpen()) {
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        deltaTime = deltaClock.restart();
        time += clock.restart();

        if (time > frameTime) {
            timer = clocker.restart();
            gameController->update();
            ButtonSwitcher::update();
            time -= frameTime;
        }
        fps.countTime(deltaTime);

        window.clear(sf::Color::Black);
        gameController->draw(window);
        window.draw(fps);
        window.display();
        ++fps;
    }
}

Game * Game::getInstance() {
    return instance;
}

sf::RenderWindow& Game::getWindow() {
    return window;
}

sf::Font * Game::getFont(){
    return &font;
}

sf::Time Game::getTimer() const {
    return timer;
}


void Game::setController(std::unique_ptr <IGame> newController) {
    gameController = std::move(newController);
}

void Game::exit(){
    window.close();
}

sf::Music * Game::getMusic() {
    return &music;
}

//void Game::boost() {
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        for (int i = 0; i < 3; ++i) timer += timer;
//}
