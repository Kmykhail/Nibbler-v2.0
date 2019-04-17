//
// Created by Kostiantyn MYKHAILENKO on 1/6/19.
//

#include "Food.hpp"
#include "Interface.hpp"
#include "global.h"
#include "Mmap.hpp"
#include "Game_Obj.hpp"
#include <random>
#define GET_VALUE_FROM_MAP(y,x) Mmap::getInstance().getValueFromMap(y, x)
#define SET_VALUE_IN_MAP(v,y,x) Mmap::getInstance().setValueInMap(v,y,x)

static int cntCreateFood = 0;

std::vector<std::pair<int, int>> Food::_coorOnMap(4, {0,0});

Food::Food() noexcept {
    _size_block = (g_weight / 90);// / 2;
    _rectLil.w = _rectLil.h = _size_block;
    _rectBig.w = _rectBig.h = _size_block * 2;
    _coorLilFood.x_arr = _coorLilFood.y_arr = _coorLilFood.y_dis = _coorLilFood.x_dis = 0;
    _coorBigFood.x_arr = _coorBigFood.y_arr = _coorBigFood.y_dis = _coorBigFood.x_dis = 0;
    _drawBig = false;
}

Food::~Food() {}

void Food::mandatoryFood() {
    if (GET_VALUE_FROM_MAP(_coorLilFood.y_arr, _coorLilFood.x_arr) != -2){//-2 on array is food
        if (_coorLilFood.y_arr != 0 & _coorLilFood.x_arr != 0) {
           Interface *qw = Interface::getInstance();
           qw->setScore(10);
        }
        cntCreateFood++;
        int x = 0;
        int y = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        do{
            std::uniform_int_distribution<> dis_x(0, 89);
            std::uniform_int_distribution<> dis_y(0, 66);
            x = dis_x(gen);
            y = dis_y(gen);
        }while(GET_VALUE_FROM_MAP(y, x) != 0);
        SET_VALUE_IN_MAP(-2, y, x);
        _coorLilFood.y_arr = y;
        _coorLilFood.x_arr = x;
        _rectLil.y = _coorLilFood.y_dis = (y * g_height / 67) + HEIGHT_SCOREBOARD; // + _size_block/2;
        _rectLil.x = _coorLilFood.x_dis = (x * g_weight / 90); // + _size_block/2;
    }
    Game_Obj::viev->drawFood(&_rectLil);
}

void Food::surpriseFood() {
    if (GET_VALUE_FROM_MAP(_coorBigFood.y_arr, _coorBigFood.x_arr) != -3) {
        if(_drawBig == true) {
            Interface *qw =  Interface::getInstance();
            qw->setScore(50);
        }
        _drawBig = false;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> createFood(0, 1);
        if (cntCreateFood && !(cntCreateFood % 5) && createFood(gen)) {//if true, create New Big Food
            cntCreateFood = 0;
            int x = 0;
            int y = 0;
            _drawBig = true;
            startBig = std::chrono::system_clock::now();
            do {
                std::uniform_int_distribution<> dis_x(0, 88);
                std::uniform_int_distribution<> dis_y(0, 65);
                x = dis_x(gen);
                y = dis_y(gen);
            } while (GET_VALUE_FROM_MAP(y, x) != 0 ||
                     GET_VALUE_FROM_MAP(y, x + 1) != 0 ||
                     GET_VALUE_FROM_MAP(y + 1, x) != 0 ||
                     GET_VALUE_FROM_MAP(y + 1, x + 1) != 0);
            _coorOnMap[0] = {y, x};
            _coorOnMap[1] = {y, x + 1};
            _coorOnMap[2] = {y + 1, x};
            _coorOnMap[3] = {y + 1, x + 1};

            for (auto& it : _coorOnMap){
                SET_VALUE_IN_MAP(-3, it.first, it.second);
            }
            _coorBigFood.y_arr = y;
            _coorBigFood.x_arr = x;
            _rectBig.y = _coorBigFood.y_dis = (_coorBigFood.y_arr * g_height / 67) + HEIGHT_SCOREBOARD;//- _size_block/2;
            _rectBig.x = _coorBigFood.x_dis = (_coorBigFood.x_arr * g_weight / 90);// - _size_block/2;
            std::cout << "_RECT_Y: " << _rectBig.y << " _RECT_X: " << _rectBig.x << std::endl;
        }
    }
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startBig);
    if (t.count() >= 8000){
        _drawBig = false;
        SET_VALUE_IN_MAP(0, _coorBigFood.y_arr, _coorBigFood.x_arr);
        for (auto& it : _coorOnMap){
            SET_VALUE_IN_MAP(0, it.first, it.second);
        }
    }
    if (_drawBig){
        Game_Obj::viev->drawBigFood(&_rectBig);
        Game_Obj::viev->drawTimeBigFood(static_cast<int>((8000 - t.count())/100));//8000
   }
}


void Food::updateFood() {
    mandatoryFood();
    surpriseFood();
}

void Food::restart() {
    SET_VALUE_IN_MAP(0, _coorLilFood.y_arr, _coorLilFood.x_arr);
    SET_VALUE_IN_MAP(0, _coorBigFood.y_arr, _coorBigFood.x_arr);

    for(auto& it : _coorOnMap){
        SET_VALUE_IN_MAP(0, it.first, it.second);
    }
    cntCreateFood = 0;
    _coorLilFood.y_arr = 0;
    _coorLilFood.x_arr = 0;
    _drawBig = false;
}

void Food::changeSize(int n) {
    _size_block = (g_weight / 90);
    _rectLil.w = _rectLil.h = _size_block;
    _rectBig.w = _rectBig.h = _size_block * 2;
    _rectLil.x = (n > 0) ? (_rectLil.x * 2) : (_rectLil.x / 2);
    _rectLil.y = (n > 0) ? (_rectLil.y * 2) : (_rectLil.y / 2);
    _coorLilFood.x_dis = (n > 0) ? ( _coorLilFood.x_dis * 2) : (_coorLilFood.x_dis / 2);
    _coorLilFood.y_dis = (n > 0) ? ( _coorLilFood.y_dis * 2) : (_coorLilFood.y_dis / 2);
    if (_drawBig == true) {
        _rectBig.x = (n > 0) ? (_rectBig.x * 2) : (_rectBig.x / 2);
        _rectBig.y = (n > 0) ? (_rectBig.y * 2) : (_rectBig.y / 2);
        _coorBigFood.x_dis = (n > 0) ? ( _coorBigFood.x_dis * 2) : (_coorBigFood.x_dis / 2);
        _coorBigFood.y_dis = (n > 0) ? ( _coorBigFood.y_dis * 2) : (_coorBigFood.y_dis / 2);
    }

}