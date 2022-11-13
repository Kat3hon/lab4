#include "Enemy.h"

void Enemy::update(float time) {
    x+=dx*time;
    timer+=time;
    if (timer>3200) {dx*=-1;timer=0;}

    if (Health<=0) {
        anim.set("dead"); dx=0;
        timer_end+=time;
        if (timer_end>4000) life=false;
    }
    anim.tick(time);
}