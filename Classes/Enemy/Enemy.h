#include "..\DynamicEntity\Entity.h"


class Enemy: public Entity {
public:
    Enemy(AnimationManager &a,Level &lev,int x,int y):Entity(a,x,y) {
        option("Enemy", 0.01, 15, "move");
    }

    void update(float time);
};
