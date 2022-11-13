#include "Projectile.h"

void Projectile::update(float time) {
    x+=dx*time;

    for (int i=0;i<obj.size();i++)
        if (getRect().intersects(obj[i].rect))
        {Health=0;}

    if (Health<=0) {anim.set("explode");dx=0;
        if (anim.isPlaying()==false) life=false;
    }
    anim.tick(time);
}