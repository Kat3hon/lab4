//
// Created by kklim on 01.11.2022.
//
#include "Game.h"
#include "..\Base\Base.h"
#include "..\MainMenu\MainMenu.h"

Game *Game::instance = nullptr;

Game::Game():window(sf::VideoMode(WIDTH, HEIGHT), "Tower Defense Game") {
    if (instance == nullptr) instance = this;

    if (!music.openFromFile("Music/mainMenuTheme.wav")) {
        MessageBox(0, "Can not open mainMenuTheme.wav", 0, 0);
        exit();
    }

    if (!icon.loadFromFile("Textures/icon.png")) {
        MessageBox(0, "Can not open icon.png", 0, 0);
        exit();
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    music.play();
    music.setLoop(true);

    gameController = std::make_unique<MainMenu>();

    accumulator = sf::Time::Zero;
    clock.restart();

    timer = sf::Time::Zero;
    clocker.restart();

    loadFont();
}

Game::~Game()
{
    instance = nullptr;
}

void Game::run()
{
    sf::Time deltaTime = sf::Time::Zero;
    sf::Clock deltaClock;

    while (window.isOpen()) {
        while (window.pollEvent(evnt))
            if (evnt.type == sf::Event::Closed)
                window.close();

        deltaTime = deltaClock.restart();
        accumulator += clock.restart();

        if (accumulator > frameTime) {
            timer = clocker.restart();
            gameController->update();
            ButtonSwitcher::update();
            accumulator -= frameTime;
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

sf::RenderWindow& Game::getWindow() const {
    return window;
}

sf::Font * Game::getFont() const {
    return &font;
}

sf::Time Game::getTimer() const {
    return timer;
}


void Game::setController(std::unique_ptr <IGame> newController) {
    gameController = std::move(newController);
}

void Game::exit() const {
    window.close();
}

sf::Music * Game::getMusic() const {
    return &music;
}

void Game::hurryUpTime() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        for (int i = 0; i < 3; ++i) timer += timer;
}

void Game::loadFont() {
    if (!font.loadFromFile("Fonts/Comfortaa.ttf"))
        MessageBox(0, "Can not load a font Comfortaa", 0, 0);
}