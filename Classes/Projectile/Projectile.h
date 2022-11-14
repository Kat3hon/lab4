#include "..\DynamicEntity\Entity.h"

class Projectile: public Entity {
public:

    Projectile(AnimationManager &a, Level &lev,int x,int y,bool dir):Entity(a,x,y) {
        option("Bullet", 0.3, 10, "move");

        if (dir) dx=-0.3;
        obj = lev.GetAllObjects("solid");
    }

    void update(float time);

};
