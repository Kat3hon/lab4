#pragma once
#include "..\baseHeaders.h"
#include "..\IController\IController.h"
#include "..\Game\Game.h"
#include "..\Level\Level.h"
#include "../Wallet/Wallet.h"

class MainGame: public IController {
private:
    Wallet wallet;

public:
    Level lvl;
    MainGame(const std::string& level_filename);
    ~MainGame() override = default;

    void update() override;
    void draw(sf::RenderWindow &window) override;
};
