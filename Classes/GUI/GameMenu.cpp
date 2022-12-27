#include "GameMenu.h"
#include "LevelMenu.h"

#include <utility>
#include <sstream>

void GameMenu::fixedUpdate(Game *game, EventStorage *events) {
    main_game.update();

    if (main_game.getWaveManager()->getWaveCooldown() == 0)
        main_game.nextWave();

    updateBindings();
}

void GameMenu::update(Game *game, EventStorage *events) {

    for (auto& it : weapons) {
        it->changeRadius();
    }

    if (events->inStock(sf::Event::EventType::MouseButtonReleased)) {
        auto event = events->at(sf::Event::EventType::MouseButtonReleased);
        if (event->mouseButton.button == sf::Mouse::Button::Left) {
            if (!(event->mouseButton.y <= 40 || event->mouseButton.x >= 480)) {
                auto tile = map.getTileFromMouse({static_cast<float>(event->mouseButton.x), static_cast<float>(event->mouseButton.y)}, *(game->getWindow()));
                if (tile != nullptr) {
                    // we found a tile, no need to look for any other GUI clicks.
                    events->pop(sf::Event::EventType::MouseButtonReleased);
                    handleTileClick(tile, game->getWindow());
                }
                else if (hasWeaponSelected())
                    deselectWeapon();
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

    health_text.setString(std::to_string(main_game.getCastle().getHealth()));
    gold_text.setString(std::to_string(main_game.getGold()));
    level_text.setString(level_name);

        const unsigned int coolDown = main_game.getWaveManager()->getWaveCooldown();

        remaining_time_text.setFillColor(sf::Color::White);

        if (coolDown <= 10) {
            if (coolDown % 2 == 0) {
                remaining_time_text.setFillColor(sf::Color::Red);
            }
        }

        unsigned int count_of_enemies = 0;
        for (auto & it : main_game.getLains()) {
            const bool enemiesPresent = it.getEnemyManager()->getEnemyCount() > 0;
            next_wave_button.setDisabled(enemiesPresent);
            next_wave_button.setColor(sf::Color{0, 125, 125, static_cast<sf::Uint8>(enemiesPresent ? 32 : 255)});
            count_of_enemies += it.getEnemyManager()->getEnemyCount();
        }
        remaining_time_text.setString(std::to_string(main_game.getWaveManager()->getWaveCooldown()));
        remaining_enemies_text.setString(std::to_string(count_of_enemies));
}

void GameMenu::setGUI(Game *game) {

    map.constructTiles();
    std::vector<Tile> tiles;
    for (auto& it: map.getTiles()) {
        tiles.push_back(it.getTile());
    }
    main_game.setPath(tiles);

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
    hydro_trap_name.setFont(font);
    hydro_trap_gold_text.setFont(font);

    health_texture.loadFromFile("assets/heart.png");
    health_sprite.setTexture(health_texture);
    gold_texture.loadFromFile("assets/gold.png");
    gold_sprite.setTexture(gold_texture);

    exit_text.setString("Exit");
    next_wave_text.setCharacterSize(17);
    next_wave_text.setString("Next wave");

    header.setSize({800.f, 40.f});
    header.setFillColor(sf::Color{255, 255, 255, 50});

    footer.setSize({120.f, 320.f});
    footer.setFillColor(sf::Color{255, 255, 255, 50});
    footer.setPosition({480.f, 40.f});

    health_sprite.setPosition(200.f, 10.f);
    health_text.setPosition(225.f, 10.f);
    health_text.setCharacterSize(15);

    gold_sprite.setPosition(125.f, 10.f);
    gold_text.setPosition(150.f, 10.f);
    gold_text.setCharacterSize(15);

    wave_text.setPosition(300.f, 10.f);
    wave_text.setCharacterSize(15);

    exit_button = createElement<MenuOption>(exit_text, 100.f, 40.f);
    exit_button.setPosition(0.f, 0.f);
    exit_button.setClickHandler([game]() { game->getSceneManager()->setScene<LevelMenu>(); });
    exit_button.setColor(sf::Color{255, 0, 0, 128});
    pushElement(&exit_button);

    next_wave_button = createElement<MenuOption>(next_wave_text, 100.f, 40.f);
    next_wave_button.setPosition(500.f, 0.f);
    next_wave_button.setClickHandler([this]() { main_game.nextWave(); });
    next_wave_button.setColor(sf::Color{255, 0, 0, 128});
    pushElement(&next_wave_button);

    remaining_time_text.setPosition(400.f, 10.f);
    remaining_time_text.setCharacterSize(13);

    remaining_enemies_text.setCharacterSize(13);
    remaining_enemies_text.setPosition(275.f, 10.f);


    // ------ shop ------

    if (!tileset.loadFromFile("assets/Level1/AllAssetsPreview.png")) {
        MessageBox(nullptr, "Can not load weapons.png", "Error!", MB_OK);
        return;
    }

    towers_textures_coords[ElementType::Hydro] = {384, 128, 16, 16};
    towers_textures_coords[ElementType::Dendro] = {336, 192, 16, 16};
    towers_textures_coords[ElementType::Cryo] = {592, 64, 16, 16};
    towers_textures_coords[ElementType::Pyro] = {272, 0, 16, 16};
    towers_textures_coords[ElementType::Electro] = {16, 16, 16, 16};

    trap_textures_coords[ElementType::Hydro] = {};
    trap_textures_coords[ElementType::Dendro] = {};
    trap_textures_coords[ElementType::Cryo] = {};
    trap_textures_coords[ElementType::Pyro] = {};
    trap_textures_coords[ElementType::Electro] = {};

    electro_tower_name.setString("ElectroTower");
    electro_tower_gold_text.setString("100");

    electro_tower_item = createElement<ShopElement>(ElementType::Electro, electro_tower_name, electro_tower_gold_text);
    electro_tower_item.setPosition(480.f, 40.f);
    electro_tower_item.setClickHandler([this](){
        selectWeapon(electro_tower_item.getTower(map.TILE_SIZE));
    });
    pushElement(&electro_tower_item);

    pyro_tower_name.setString("PyroTower");
    pyro_tower_gold_text.setString("100");

    pyro_tower_item = createElement<ShopElement>(ElementType::Pyro, pyro_tower_name, pyro_tower_gold_text);
    pyro_tower_item.setPosition(480.f, 140.f);
    pyro_tower_item.setClickHandler([this]() {
        selectWeapon(pyro_tower_item.getTower(map.TILE_SIZE));
    });
    pushElement(&pyro_tower_item);

    hydro_trap_name.setString("HydroTrap");
    hydro_trap_gold_text.setString("50");

    hydro_trap_item = createElement<ShopElement>(ElementType::Hydro, hydro_trap_name, hydro_trap_gold_text);
    hydro_trap_item.setPosition(480.f, 240.f);
    hydro_trap_item.setClickHandler([this]() {
        selectWeapon(hydro_trap_item.getTrap(map.TILE_SIZE));
    });
    pushElement(&hydro_trap_item);
}

void GameMenu::draw(sf::RenderWindow &window) const {
    map.draw(window);
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
    window.draw(hydro_trap_item);

    for (const auto& it : weapons)
        it->draw(window, sf::RenderStates::Default);



}

void GameMenu::handleTileClick(TileGUI* tile, sf::RenderWindow* window) {

    if(hasWeaponSelected())
        getSelectedWeapon()->setSelected(false);
    if (!tile->getTile().isBuildable()) {
        current_weapon.reset();
        return;
    }
    std::cout << "1" << std::endl;
    if (!tile->getTile().hasWeapon() &&  hasWeaponSelected() && !(current_weapon->isBuilt()) && tile->getTile().getType()==current_weapon->isBuildable()) {

        std::cout << "2" << std::endl;
        if (main_game.getGold() < current_weapon->getWeapon()->getGold()) {
            current_weapon.reset();
            return;
        }

        main_game.substractGold(current_weapon->getWeapon()->getGold());

        tile->getTile().setWeapon(current_weapon->getWeapon());
        current_weapon->setTexture(tileset, towers_textures_coords[current_weapon->getWeapon()->getElementType()]);
        main_game.getWeaponManager()->push(current_weapon->getWeapon());

        current_weapon->getSprite().setPosition(tile->getTile().getX(), tile->getTile().getY());
        current_weapon->setSelected(true);
        current_weapon->build();
        weapons.push_back(current_weapon);
        return;
    }

    //Level up weapon
    if (tile->getTile().hasWeapon()) {
        if (main_game.getGold() < tile->getTile().getWeapon()->getGold() ||
            tile->getTile().getWeapon()->getDamage() == 50) {
            return;
        }

        if (hasWeaponSelected())
            deselectWeapon();

        if(tile->getTile().getWeapon()->canBeLeveledUp()) {
            tile->getTile().getWeapon()->levelUp();
            // можно сделать чтоб была таблица стоимости улучшений уровня
            main_game.substractGold(tile->getTile().getWeapon()->getGold());
        }
        return;

    }

}

bool GameMenu::hasWeaponSelected() {
    return current_weapon != nullptr;
}

WeaponGUI::Ptr GameMenu::getSelectedWeapon() const {
    return current_weapon;
}

void GameMenu::deselectWeapon() {
    current_weapon->setSelected(false);
    current_weapon.reset();
}

void GameMenu::selectWeapon(const WeaponGUI::Ptr &weapon) {
    current_weapon = weapon;
}
