//
// Created by kklim on 01.11.2022.
//

#ifndef LAB4_LANDSCAPE_H
#define LAB4_LANDSCAPE_H

#include <iostream>

class LANDSCAPE {
private:
    const size_t dimx_; //длина поля в клетках
    const size_t dimy_; //ширина поля в клетках
    std::vector<Cell> game_field;
public:
    LANDSCAPE():dimx_(0),dimy_(0) {};

};

#endif //LAB4_LANDSCAPE_H
