#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "..\AnimationManager\AnimationManager.h"
#include "..\Level\Level.h"
#include "..\baseHeaders.h"

class Entity {
public:
    float x,y,dx,dy,w,h;
    AnimationManager anim;
    std::vector<Object> obj; //вектор объектов карты
    bool life, dir;
    float timer, timer_end;
    std::string Name;
    int Health;

    Entity(AnimationManager &A,int X, int Y);
    virtual void update(float time) = 0;
    void draw(RenderWindow &window);
    FloatRect getRect(); //получение размеров прямоугольника - хитбокса объекта (x,y,w,h)
    void option(std::string NAME, float SPEED=0, int HEALTH=10, std::string FIRST_ANIM="");
    virtual bool isDead(); //проверяет мертв ли объект
};


