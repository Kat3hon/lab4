#pragma once

#include "Weapon.h"
#include "WeaponManager.h"
#include "Castle.h"
#include "Lain.h"

#include <memory>
#include <functional>

//#include <SFML/System/Clock.hpp>
//#include <SFML/System/NonCopyable.hpp>
//#include <SFML/Graphics/Drawable.hpp>
//#include <SFML/Graphics/RenderStates.hpp>
//#include <SFML/Graphics/RenderTarget.hpp>

class MainGame {

    unsigned int gold = 1000;

    class Castle castle;
    std::vector<class Lain> lains;

    WeaponManager weapon_manager;

public:

    MainGame() = default;

    void update();

    void addGold(unsigned int amount);

    void substractGold(unsigned int amount);

    void setGold(unsigned int amount);

    unsigned int getGold() const;

    WeaponManager *getWeaponManager();

    void onEnemyKilled(const Enemy::Ptr &enemy);

    void onEnemyDestination(const Enemy::Ptr &enemy);
};

