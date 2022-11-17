#include "..\DynamicEntity\Entity.h"

class Projectile: public Entity {
private:
    ELEMENT element; //вид элемента снаряда

public:

    Projectile(AnimationManager &a, Level &lev,int x,int y,bool dir):Entity(a,x,y) {
        option("Bullet", 0.3, 10, "move"); //непосредственно создаём динамический объект с анимацией движения

        if (dir) dx=-0.3;
        obj = lev.GetAllObjects("solid");
    }

    bool isDead() override;

    void update(float time) override;

};
