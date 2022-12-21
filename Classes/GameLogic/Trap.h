#include "Weapon.h"

class Trap: public Weapon {

public:
    explicit Trap(ElementType elementType);
    void attack() override;
};

