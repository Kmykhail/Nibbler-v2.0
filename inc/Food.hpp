//
// Created by Kostiantyn MYKHAILENKO on 1/6/19.
//

#pragma once

#include <vector>
#include "header.h"
#include "Interface.hpp"

class Food {
public:
    explicit Food() noexcept;
    Food(const Food &) = delete;
    Food(Food &&) = delete;
    Food &operator=(const Food&) = delete;
    Food &operator=(Food&&) = delete;
    ~Food();

    void    updateFood();
    void    restart();
    void    changeSize(int);
    static std::vector<std::pair<int, int>> _coorOnMap;

private:
    void    mandatoryFood();
    void    surpriseFood();
    t_scr _rectLil;
    t_scr _rectBig;
    t_coor _coorLilFood;
    t_coor _coorBigFood;

    int _size_block;
    bool _drawBig;
    std::chrono::time_point<std::chrono::system_clock> startBig;
};

