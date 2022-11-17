#pragma once
#include "../baseHeaders.h"
#include "../Enemy/Enemy.h"
#include <queue>

class Wave {
    std::queue <std::pair<Enemy, size_t>> enemies; //очередь из врагов, которые выпускаются в соответствии со временем от начала волны


public:

    bool isEmpty(); //проверяет пустая ли очередь из врагов
    bool releaseEnemy(); //выпускает очередного врага из очереди
    bool update(); //обновляет состояние волны, сравнивая с таймером игры

};
