//
// Created by Kostiantyn MYKHAILENKO on 1/6/19.
//

#include "Food.hpp"
#include "global.h"
#include "Mmap.hpp"
#include "SDL_lib.hpp"

Food::Food() noexcept {
    _size_block = (g_weight / 90) / 2;
    _rectLil.w = _rectLil.h = _size_block;
    _coors.x_arr = _coors.y_arr = _coors.y_dis = _coors.x_dis = 0;
}

Food::~Food() {

}

void Food::mandatoryFood() {
    if (Mmap::getInstance().getValueFromMap(_coors.y_arr, _coors.x_arr) != -2){//-2 on array is food
        int x = 0;
        int y = 0;
        static int step = 0;
        do{
//            x = rand() % 90;
//            y = rand() % 67;
            x = 11;
            y = 5 + step;
        }while(Mmap::getInstance().getValueFromMap(y, x) != 0);
        step++;
        std::cout << "y: " << y << " x: " << x << std::endl;
        Mmap::getInstance().setValueInMap(-2, y, x);
        Mmap::getInstance().printMmap();
        _coors.y_arr = y;
        _coors.x_arr = x;
        _rectLil.y = _coors.y_dis = y * g_height / 67 + HEIGHT_SCOREBOARD;
        _rectLil.x = _coors.x_dis = x * g_weight / 90;
        std::cout << "screen_y: " << _rectLil.y << " screen_x: " << _rectLil.x << std::endl;
    }
    switch (g_lib){
        case 1:
            SDL_lib::getInstance().drawFood(&_rectLil);
            break;
        case 2:
            //TODO call sfml.draw();
            break;
        case 3:
            //TODO call allegro.draw();
            break;
        default:
            break;
    }
}

void Food::surpriseFood() {}

void Food::updateFood() {
    mandatoryFood();
    surpriseFood();
}