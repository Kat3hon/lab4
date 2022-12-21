#pragma once
#include <memory>

class Weapon;

class Enemy;

class IWeapon{
public:
    virtual void onWeaponShoot(const std::shared_ptr<Weapon> &weapon) = 0;

    virtual void onWeaponBulletHit(const std::shared_ptr<Weapon> &weapon, const std::shared_ptr<Enemy> &enemy) = 0;
};
