#include "MainMenu.h"

MainMenu::MainMenu():buttonPressed(0) {
    //без этого появляются белые квадраты вместо текстур:
    // Вектор изначально выделяет некоторую память, и,
    // когда нет места для вставки нового элемента,
    // вектор выделяет больше памяти и копирует туда все вставленные элементы и новый.
    // Так что все адреса предметов меняются.
    //В вашем случае элемент является текстурой,
    // его адрес изменяется при воздействии другой текстуры,
    // поэтому некоторые спрайты «теряют» свою текстуру.

    option.resize(3);
    if (Game::instance->getMusicPtr()->getStatus() == sf::Music::Stopped)
        Game::instance->getMusicPtr()->play();

    option.emplace_back(MenuOption());
    if (!option[0].texture.loadFromFile("../Storage/Textures/Menu/Title.png")) {
        MessageBox(nullptr, "Can not load Title.png", "Error!", MB_OK);
        Game::instance->getWindowPtr()->close();
    }
    option[0].sprite.setTexture(option[0].texture);
    option[0].width = WIDTH / 6.;
    option[0].height = HEIGHT * 0.25;
    option[0].sprite.setPosition(option[0].width, option[0].height);
    option[0].id = 0;

    option.emplace_back(MenuOption());
    if(!option[1].texture.loadFromFile("../Storage/Textures/Menu/Start.png")) {
        MessageBox(nullptr, "Can not load Start.png", "Error!", MB_OK);
        Game::instance->getWindowPtr()->close();
    }
    option[1].sprite.setTexture(option[1].texture);
    option[1].width = WIDTH / 2.5;
    option[1].height = HEIGHT * 0.45;
    option[1].sprite.setPosition(option[1].width, option[1].height);
    option[1].id = 1;

    option.emplace_back(MenuOption());
    if(!option[2].texture.loadFromFile("../Storage/Textures/Menu/Exit.png")){
        MessageBox(nullptr, "Can not load Exit.png", "Error!", MB_OK);
        Game::instance->getWindowPtr()->close();
    }
    option[2].sprite.setTexture(option[2].texture);
    option[2].width = WIDTH / 2.5;
    option[2].height = HEIGHT*0.65;
    option[2].sprite.setPosition(option[2].width, option[2].height);
    option[2].id = 2;

}

void MainMenu::update() {
    for (auto& item : option)
        item.setColor(Color::White);

    for (auto & item : option) {
        //почему то при изменении размеров экрана ничего не меняется, то есть надо водить мышкой вне окна для изменения цвета
        if (item.getID()!= 0 && IntRect(0, item.getHeight(), Game::instance->getWindowPtr()->getSize().x, 0.1*Game::instance->getWindowPtr()->getSize().y).contains(Mouse::getPosition(*Game::instance->getWindowPtr()))) {
            item.setColor(Color::Yellow);
            buttonPressed = item.getID();
        }
    }

    //проблема: при смене меню инпут проходит далее, то есть при закрытии меню в левел меню происходит тот же кейс в меню выше - мейн меню
    //это из-за того что мышка находится в том же прямоугольнике
    //костыльное решение: сдвигать курсор в верхний левый угол - там точно не будет никаких прямоугольников

    if (Mouse::isButtonPressed(Mouse::Left)) {
        switch(buttonPressed) {
            case 1: {
                sf::Vector2 pos = {0, 0};
                Mouse::setPosition(pos);
                Game::instance->setController(std::make_unique<LevelMenu>());
            } break;
            case 2: Game::instance->getWindowPtr()->close(); break;
        }
    }

}

void MainMenu::draw(sf::RenderWindow & window) {
    for (const auto & i: option)
        window.draw(i.getSprite());
}
