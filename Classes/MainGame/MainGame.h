#include "..\baseHeaders.h"
#include "..\IController\IController.h"
#include "..\Game\Game.h"
#include "..\Level\Level.h"

class MainGame: public IController {
private:

public:
    Level lvl;
    MainGame(const std::string& level_filename);
    ~MainGame();

    void update() override;
    void draw(sf::RenderWindow &window) override;
};
