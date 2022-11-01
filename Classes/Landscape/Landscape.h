//
// Created by kklim on 01.11.2022.
//

#ifndef LAB4_LANDSCAPE_H
#define LAB4_LANDSCAPE_H

#include <iostream>
#include <vector>
#include "..\Cell\Cell.h"

class Landscape {
private:
    std::pair <size_t, size_t> field_size;
    std::vector<Cell> game_field; //сжатая в вектор матрица клеток игрового поля
public:
    Landscape(size_t dimx_ = 1000, size_t dimy_ = 1000):field_size(dimx_, dimy_) {};

};

#endif //LAB4_LANDSCAPE_H
