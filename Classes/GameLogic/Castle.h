#pragma once

#include "Enemy.h"

class Castle {

    unsigned int health = 1000;

public:
    void addHealth(unsigned int health);

    void substractHealth(unsigned int health);

    void setHealth(unsigned int health);

    [[nodiscard]] unsigned int getHealth() const;

};

