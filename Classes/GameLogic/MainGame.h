#include "grid.hpp"
#include "tower/tower.hpp"
#include "tower/towerManager.hpp"
#include "wave/waveManager.hpp"
#include "enemy/enemyManager.hpp"

#include <memory>
#include <functional>

#include <SFML/System/Clock.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class MainGame : public sf::Drawable, public sf::NonCopyable {

    //Checks to see what enemies can be spawned
    void spawnEnemies();

    void spawnEnemy(const Enemy::Ptr& enemy);

    unsigned int m_health;
    unsigned int m_gold;

    Grid m_grid;

    TowerManager m_towerManager;
    WaveManager m_waveManager;
    EnemyManager m_enemyManager;

    Tower::Ptr m_currentSelectedTower;

    sf::Clock m_lastEnemySpawned;

public:

    MainGame();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void tick();

    void addGold(unsigned int amount);

    void substractGold(unsigned int amount);

    void setGold(unsigned int amount);

    unsigned int getGold();

    void addHealth(unsigned int health);

    void substractHealth(unsigned int health);

    void setHealth(unsigned int health);

    unsigned int getHealth();

    void nextWave();

    Grid *getGrid();

    void selectTower(const Tower::Ptr& tower);

    void handleTileClick(const Tile::Ptr &tile);

    void deselectTower();

    bool hasTowerSelected();

    void onEnemyDestination(const Enemy::Ptr& enemy);

    void onEnemyKilled(const Enemy::Ptr& enemy);

    Tower::Ptr getSelectedTower();

    TowerManager *getTowerManager();

    WaveManager *getWaveManager();

    EnemyManager *getEnemyManager();
};

