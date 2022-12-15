#pragma once
#include <memory>

class Tower;

class Enemy;

class ITower{
public:
    virtual void onTowerShoot(const std::shared_ptr<Tower> &tower) = 0;

    virtual void onTowerBulletHit(const std::shared_ptr<Tower> &tower, const std::shared_ptr<Enemy> &enemy) = 0;
};
