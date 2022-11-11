#include "../MainMenu/MainMenu.h"
#include "Game.h"

Game* Game::instance = nullptr;
const sf::Time Game::frameTime = sf::seconds(1.f / 120.f);


Game::Game(): window(sf::VideoMode(WIDTH, HEIGHT), "MYFAROG") {

    if (instance == nullptr)
        instance = this;
    window.setFramerateLimit(120);
    //set main menu music
    if (!music.openFromFile("../Storage/Music/mainMenuTheme.wav")) {
        MessageBox(nullptr, "Can not load mainMenuTheme.wav", "Error!", MB_OK);
        window.close();
    }
    music.play();
    music.setLoop(true);

    //set icon
    if (!icon.loadFromFile("../Storage/Textures/icon.png")) {
        MessageBox(nullptr, "Can not load icon.png", "Error!", MB_OK);
        exit();
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //set font
    if (!font.loadFromFile("../Storage/Fonts/Comfortaa.ttf"))
        MessageBox(nullptr, "Can not load Comfortaa.ttf", "Error!", MB_OK);

    currentController = std::make_unique<MainMenu>();
}

Game::~Game() { instance = nullptr; }

void Game::run() {
    sf::Time dTime = sf::Time::Zero;
    sf::Clock dClock;

    while (window.isOpen()) {
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        dTime = dClock.restart();
        time += clock.restart();

        if (time > frameTime) {
            //timer = clocker.restart();
            currentController->update();
            //ButtonSwitcher::update();
            time -= frameTime;
        }
        fps.countTime(dTime);

        window.clear(Color::Black);
        window.draw(fps);
        currentController->draw(window);
        window.display();
        ++fps;
    }
}

void Game::setController(std::unique_ptr <IController> newMenu) {
    currentController = std::move(newMenu);
}


void Game::exit() {
    window.close();
}

//game acceletation with space button
//void Game::boost() {
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        for (int i = 0; i < 3; ++i) timer += timer;
//}
