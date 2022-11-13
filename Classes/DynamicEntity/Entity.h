#include <SFML/Graphics.hpp>
#include <vector>
#include "..\AnimationManager\AnimationManager.h"
#include "..\Level\Level.h"
#include "..\baseHeaders.h"

class Entity {
public:
    float x,y,dx,dy,w,h;
    AnimationManager anim;
    std::vector<Object> obj;
    bool life, dir;
    float timer, timer_end;
    std::string Name;
    int Health;

    Entity(AnimationManager &A,int X, int Y);
    virtual void update(float time) = 0;
    void draw(RenderWindow &window);
    FloatRect getRect();
    void option(std::string NAME, float SPEED=0, int HEALTH=10, std::string FIRST_ANIM="");
};


