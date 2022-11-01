//
// Created by kklim on 02.11.2022.
//

#include "MainMenu.h"
#include "..\Base\Base.h"
#include "..\Game\Game.h"
#include "..\LevelMenu\LevelMenu.h"

MainMenu::MainMenu() {
    sf::Music *mainMenuMusic = Game::getInstance()->getMusic();

    if (mainMenuMusic->getStatus() == sf::Music::Stopped)
        mainMenuMusic->play();

    title.setFont(font);
    title.setColor(sf::Color::Blue);
    title.setCharacterSize(70);
    title.setString("Tower Defense Game");
    title.setPosition(WIDTH/2 - title.getGlobalBounds().width/2,HEIGHT * 1/4);

    buttons.push_back(button());
    buttons[0].setFont(font);
    buttons[0].setString("Start Game !");
    buttons[0].setCharacterSize(50);
    buttons[0].setPosition(WIDTH / 2 - buttons[0].getGlobalBounds().width / 2, HEIGHT * 1 / 2);

    buttons.push_back(button());
    buttons[1].setFont(font);
    buttons[1].setString("Exit Game");
    buttons[1].setCharacterSize(50);
    buttons[1].setPosition(WIDTH / 2 - buttons[1].getGlobalBounds().width / 2, HEIGHT * 2/3);

    currentButton = 0;

    buttons[currentButton].increase();
}

MainMenu::~MainMenu() {
}

void MainMenu::update() {
    particleSystem.update();
    handleButtons();

}

void MainMenu::draw(sf::RenderWindow & window) const {
    window.draw(title);

    for (int i = 0; i < buttons.size(); ++i) {
        window.draw(buttons[i]);
    }
    window.draw(particleSystem);
}

void MainMenu::handleButtons() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (currentButton < buttons.size() - 1) {
            buttons[currentButton].decrease();
            currentButton++;
            buttons[currentButton].increase();
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (currentButton > 0) {
            buttons[currentButton].decrease();
            currentButton--;
            buttons[currentButton].increase();
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        followFunc(currentButton);
    }

    sf::Vector2f mousePos = getMousePos();

    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].getGlobalBounds().contains(mousePos)) {
            if ((buttonSwitcher::canClick() && (sf::Mouse::isButtonPressed(sf::Mouse::Left))))
                followFunc(currentButton);

            if (i == currentButton)
                continue;

            buttons[currentButton].decrease();
            currentButton = int(i);
            buttons[currentButton].increase();
        }
    }
}

void MainMenu::followFunc(int index)
{
    switch (index) {
        case 0: Game::getInstance()->setController(std::make_unique<choiceLevelMenu>()); break;
        case 1: Game::getInstance()->exit(); break;
        default: break; //???
    }
}