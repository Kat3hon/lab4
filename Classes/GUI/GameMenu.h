#pragma once

#include "Scene.h"
#include "MenuOption.h"
#include "../GameLogic/MainGame.h"
#include "Game.h"
#include "ShopElement.h"
#include "Level.h"
#include "WeaponGUI.h"

#include <string>
#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameMenu : public Scene {

    const unsigned int TOWER_COST = 100;

    sf::Text wave_text;
    sf::Text health_text;
    sf::Text gold_text;
    sf::Text exit_text;
    sf::Text level_text;
    sf::Text next_wave_text;
    sf::Text remaining_time_text;
    sf::Text remaining_enemies_text;

    sf::Sprite ground_sprite;
    sf::Texture ground_texture;

    sf::Sprite gold_sprite;
    sf::Texture gold_texture;

    sf::Sprite health_sprite;
    sf::Texture health_texture;

    sf::RectangleShape header;
    sf::RectangleShape footer;

    MenuOption exit_button;
    MenuOption next_wave_button;

    std::string level_name;

    MainGame main_game;

    // separated for shop
    ShopElement electro_tower_item;
    sf::Text electro_tower_name;
    sf::Text electro_tower_gold_text;

    ShopElement pyro_tower_item;
    sf::Text pyro_tower_name;
    sf::Text pyro_tower_gold_text;

    ShopElement hydro_trap_item;
    sf::Text hydro_trap_name;
    sf::Text hydro_trap_gold_text;

    Level map;

    WeaponGUI::Ptr current_weapon;

    void updateBindings();

public:

    explicit GameMenu(std::string levelName)
            : Scene(), level_name(std::move(levelName)) {
        try {
            map.loadFromFile("assets/"+level_name+"/"+level_name+".tmx");
        }
        catch(const std::exception& ex) {
            std::cout << ex.what() << std::endl;
            MessageBox(nullptr, ex.what(), "Error!", MB_OK);
        }
    }

    void fixedUpdate(Game *game, EventStorage *events) override;

    void update(Game *game, EventStorage *events) override;

    void enter(Game *game) override;

    void setGUI(Game *game) override;

    void draw(sf::RenderWindow &window) const override;

    WeaponGUI::Ptr getSelectedWeapon() const;

    bool hasWeaponSelected();

    void deselectWeapon();

    void selectWeapon(const WeaponGUI::Ptr &weapon);

    void handleTileClick(const TileGUI::Ptr &tile);
};

