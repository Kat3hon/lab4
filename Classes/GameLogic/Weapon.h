#pragma once

#include "ElementType.h"
#include "../GUI/GameObject.h"
#include "Enemy.h"
#include "IWeapon.h"
#include "Weapon.h"
#include "WeaponType.h"

#include <memory>
#include <vector>


class Weapon: public GameObject {

    /// Range of the weapon.
    unsigned int range;

    /// Damage of the weapon.
    unsigned int damage;

    /// Type of tower: Hydro, Dendro, Cryo, Pyro or Electro.
    ElementType type;

    std::vector<IWeapon> interfaces;

    /// Current enemy in radius of weapon
    std::weak_ptr<Enemy> curr_focussed_enemy;

public:

    using Ptr = std::shared_ptr<Weapon>;

    explicit Weapon(ElementType elementType);

    bool hasLockOn();

    /// this function will be used
    /// to check if the enemy is still in range of weapon radius.
    /// if not, deselect the current focused enemy.
    void validateLockOn();

    Enemy::Ptr getLockOn();

    void lockOn(std::weak_ptr<Enemy> enemy);

    virtual void attack() = 0;

    bool isInRange(const Enemy::Ptr& enemy);

    unsigned int getRange() const;

    unsigned int getDamage() const;

    ElementType getElementType() const;

    void setRange(unsigned int range_var);

    void setDamage(unsigned int damage_var);

};

