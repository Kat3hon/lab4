#pragma once
#include "../Storage/tinyxml/tinyxml2.h"
#include "../baseHeaders.h"

class Animation {
public:
    std::vector<IntRect> frames, frames_flip; //вектор прямоугольников, определяющих анимацию, они задаются в AnimationManager
    //frames_flip - отзеркаленные те же изображения
    float currentFrame, speed; //текущий фрейм, скорость анимации
    bool loop;   // показывает зациклена ли анимация
    bool flip;  // определяет имеет ли анимация зеркальную копию
    bool isPlaying; //проигрывается ли сейчас анимация или стоит на месте?
    Sprite sprite;

    Animation():currentFrame(0), isPlaying(true), flip(false), loop(true) {}

    void tick(float time); //прокрутка анимации в зависимости от времени

};

