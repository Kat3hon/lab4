#include "GameMenu.h"
#include "LevelMenu.h"

#include <utility>
#include <sstream>

void GameMenu::fixedUpdate(Game *game, EventStorage *events) {
    main_game.tick();

    if (main_game.getWaveManager()->getWaveCooldown() == 0)
        main_game.nextWave();

    updateBindings();
}

void GameMenu::update(Game *game, EventStorage *events) {

    if (events->inStock(sf::Event::EventType::MouseButtonReleased)) {
        auto event = events->at(sf::Event::EventType::MouseButtonReleased);
        if (event->mouseButton.button == sf::Mouse::Button::Left) {
            auto tile = main_game.getGrid()->getTileFromMouse({event->mouseButton.x, event->mouseButton.y});
            if (tile != nullptr) {
                // we found a tile, no need to look for any other GUI clicks.
                events->pop(sf::Event::EventType::MouseButtonReleased);
                main_game.handleTileClick(tile);
            }
            else {
                if (main_game.hasTowerSelected()) {
                    main_game.deselectTower();
                }
            }
        }
    }

    Scene::update(game, events);
}

void GameMenu::enter(Game *game) {
    updateBindings();
}

void GameMenu::updateBindings() {

    std::ostringstream waveText;
    waveText << "Wave: " << std::to_string(main_game.getWaveManager()->getCurrentWaveNo());
    wave_text.setString(waveText.str());

    health_text.setString(std::to_string(main_game.getHealth()));
    gold_text.setString(std::to_string(main_game.getGold()));
    level_text.setString(level_name);

    const unsigned int coolDown = main_game.getWaveManager()->getWaveCooldown();

    remaining_time_text.setFillColor(sf::Color::White);

    if (coolDown <= 10) {
        if (coolDown % 2 == 0) {
            remaining_time_text.setFillColor(sf::Color::Red);
        }
    }

    const bool enemiesPresent = main_game.getEnemyManager()->getEnemyCount() > 0;
    next_wave_button.setDisabled(enemiesPresent);
    next_wave_button.setColor(sf::Color{0, 125, 125, static_cast<sf::Uint8>(enemiesPresent ? 32 : 255)});

    remaining_time_text.setString(std::to_string(main_game.getWaveManager()->getWaveCooldown()));
    remaining_enemies_text.setString(std::to_string(main_game.getEnemyManager()->getEnemyCount()));
}

void GameMenu::setGUI(Game *game) {

    main_game.getGrid()->setPosition(150, 150);

    wave_text.setFont(font);
    health_text.setFont(font);
    gold_text.setFont(font);
    exit_text.setFont(font);
    level_text.setFont(font);
    next_wave_text.setFont(font);
    remaining_time_text.setFont(font);
    remaining_enemies_text.setFont(font);
    electro_tower_name.setFont(font);
    electro_tower_gold_text.setFont(font);
    pyro_tower_gold_text.setFont(font);
    pyro_tower_name.setFont(font);

    health_texture.loadFromFile("asset/heart.png");
    health_sprite.setTexture(health_texture);
    gold_texture.loadFromFile("asset/gold.png");
    gold_sprite.setTexture(gold_texture);

    exit_text.setString("Exit");
    next_wave_text.setCharacterSize(17);
    next_wave_text.setString("Next wave");

    header.setSize({800.f, 40.f});
    header.setFillColor(sf::Color{255, 255, 255, 50});

    footer.setSize({800.f, 120.f});
    footer.setFillColor(sf::Color{255, 255, 255, 50});
    footer.setPosition({0.f, 800.f - footer.getSize().y});

    health_sprite.setPosition(400.f, 10.f);
    health_text.setPosition(425.f, 10.f);
    health_text.setCharacterSize(15);

    gold_sprite.setPosition(250.f, 10.f);
    gold_text.setPosition(275.f, 10.f);
    gold_text.setCharacterSize(15);

    wave_text.setPosition(500.f, 10.f);
    wave_text.setCharacterSize(15);

    exit_button = createElement<MenuOption>(exit_text, 100.f, 40.f);
    exit_button.setPosition(0.f, 0.f);
    exit_button.setClickHandler([game]() { game->getSceneManager()->setScene<LevelMenu>(); });
    exit_button.setColor(sf::Color{255, 0, 0, 128});
    pushElement(&exit_button);

    next_wave_button = createElement<MenuOption>(next_wave_text, 100.f, 40.f);
    next_wave_button.setPosition(700.f, 0.f);
    next_wave_button.setClickHandler([this]() { main_game.nextWave(); });
    pushElement(&next_wave_button);

    remaining_time_text.setPosition(675.f, 10.f);
    remaining_time_text.setCharacterSize(13);

    remaining_enemies_text.setCharacterSize(13);
    remaining_enemies_text.setPosition(600.f, 10.f);


    // ------ shop ------

    electro_tower_name.setString("Electric");
    electro_tower_gold_text.setString("100");

    electro_tower_item = createElement<ShopElement>(TowerType::ElectroTower, electro_tower_name, electro_tower_gold_text);
    electro_tower_item.setPosition(0.f, 680.f);
    electro_tower_item.setClickHandler([this](){
        main_game.selectTower(electro_tower_item.get());
    });
    pushElement(&electro_tower_item);

    pyro_tower_name.setString("Pyro");
    pyro_tower_gold_text.setString("100");

    pyro_tower_item = createElement<ShopElement>(TowerType::BombTower, pyro_tower_name, pyro_tower_gold_text);
    pyro_tower_item.setPosition(120.f, 680.f);
    pyro_tower_item.setClickHandler([this]() {
        main_game.selectTower(pyro_tower_item.get());
    });
    pushElement(&pyro_tower_item);
}

void GameMenu::draw(sf::RenderWindow &window) const {
    window.draw(header);
    window.draw(footer);
    window.draw(wave_text);
    window.draw(gold_text);
    window.draw(health_text);
    window.draw(health_sprite);
    window.draw(gold_sprite);
    window.draw(exit_button);
    window.draw(remaining_time_text);
    window.draw(remaining_enemies_text);
    window.draw(next_wave_button);
    window.draw(electro_tower_item);
    window.draw(pyro_tower_item);
    window.draw(main_game);
}
