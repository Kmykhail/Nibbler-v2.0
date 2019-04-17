//
// Created by kmykhailenko on 31.12.18.
//

#include "Logic.hpp"
#include "global.h"
#include <iterator>
#include <iostream>
#include "Mmap.hpp"
#include "Game_Obj.hpp"

int const FPS = 60;

Logic::Logic() noexcept {
    _size_block = g_weight / 90;
    _rect.w = _rect.h = _size_block;
    _playGame = true;
}

void Logic::init(int n_pl) {
    _pl = n_pl;
    int x = 0;
    int y = 0;
    if (_pl == 1) {
        _key = 'd'; //TODO rand direction
        x = 2 * g_weight / 90;//place on screen, x
        y = 5 * g_height / 67;//place on screen, y
    }
    else if (_pl > 1){
        _key = 'a';
        x = 88 * g_weight / 90;//place on screen, x
        y = 10 * g_height / 67;//place on screen, y
    }
    for (int i = 0; i < 4; ++i) {
        int j = 0;
        if (i > 0 && i < 4){
            j = (i > 0 && i < 3) ? 1 : 2;
        }
        if (_key == 'd') {
            _cors.push_back({y + HEIGHT_SCOREBOARD, x + (_size_block * i), y * 67 / g_height, (x * 90 / g_weight) + i});
            Mmap::getInstance().setValueInMap(-1, y * 67 / g_height, (x * 90 / g_weight) + i);
        }
        else if (_key == 'a'){
            _cors.push_back({y + HEIGHT_SCOREBOARD, x - (_size_block * i), y * 67 / g_height - 1, (x * 90 / g_weight - 1) - i});
            Mmap::getInstance().setValueInMap(-1, (y * 67 / g_height - 1), ((x * 90 / g_weight) - 1) - i);
        }
        _rect.y = _cors.back().y_dis;
        _rect.x = _cors.back().x_dis;
         Game_Obj::viev->drawSnake(&_rect, j);
    }
}

//int Logic::getNumberSprite(int itr) {
//    if (!itr){
//        return 0;
//    }
//    else if (itr < _cors.size() - 1){
//        return 1;
//    }
//    return 2;
//}

void Logic::setKey(int key) {
    if (key >= 123 && key <= 126 && _pl == 2){
        if (key == 126 || key == 125){
            _key = (key == 126) ? 'w' : 's';
        }
        else if(key == 124 || key == 123){
            _key = (key == 124) ? 'd' : 'a';
        }
    }
    else if (_pl == 1){
        if ((key == 'w' && _key != 's') || (key == 's' && _key != 'w')) {
            _key = static_cast<char>(key);
        }
        else if ((key == 'a' && _key != 'd') || (key == 'd' && _key != 'a')){
            _key = static_cast<char>(key);
        }
    }
}

void Logic::updateHead(t_coor& head) {
    if (_key == 'a' || _key == 'd'){
        head.x_dis += (_key == 'd') ? _size_block : -_size_block;
        head.x_arr += (_key == 'd') ? 1 : -1;
    }
    else if (_key == 'w' || _key == 's'){
        head.y_dis += (_key == 's') ? _size_block : -_size_block;
        head.y_arr += (_key == 's') ? 1 : -1;
    }
}

void Logic::move() {
    _size_block = g_weight / 90;
    _rect.w = _rect.h = _size_block;
    t_coor head = _cors.back();
    updateHead(head);
    int ch = Mmap::getInstance().getValueFromMap(head.y_arr, head.x_arr);
    if (ch > 0 || ch == -1){
        Game_Obj::_frameDelay = 4000 / FPS;
        Game_Obj::music->playCrash();
        crash();
        return;
    }
    else if (ch == -2 || ch == -3){ //-2 small food and -3 big food
        Game_Obj::_frameDelay -= (Game_Obj::_frameDelay > 20) ? 2 : 0;
        grow(ch);
        Game_Obj::music->playEat();
    }
    
    else if (ch == -5) { // portal
        head.x_arr = (head.x_arr == 0) ? 88 : 1;
        head.x_dis = (head.x_arr *  g_weight) / 90;
    }

    for(auto it = _cors.begin(), it_c = ++_cors.begin(); it != _cors.end(); it++){
        int j = 0;

        if (it == _cors.begin() && it_c != _cors.end()){
            j = 1;
        }
        else if (it != _cors.begin() && it_c == _cors.end()){
            j = 2;
        }

        if (it == _cors.begin()){
            Mmap::getInstance().setValueInMap(0, it->y_arr, it->x_arr);
        }
        if (it_c != _cors.end()) {
            *it = *it_c;
            it_c++;
        }
        else if(it_c == _cors.end()){
            *it = head;
            Mmap::getInstance().setValueInMap(-1, it->y_arr, it->x_arr);
        }
        _rect.y = it->y_dis;
        _rect.x = it->x_dis;
        Game_Obj::viev->drawSnake(&_rect, j);
    }
}

void Logic::restart() {
    for(auto it : _cors){
        Mmap::getInstance().setValueInMap(0, it.y_arr, it.x_arr);
    }
    _cors.erase(_cors.begin(), _cors.end());
    init(1);
    _playGame = true;
    _key = (_pl == 1) ? 'd' : 'a';
}

bool Logic::runningGame() const { return _playGame;}

void Logic::crash() {
    _playGame = false;
}

void Logic::grow(int typeFood) {
    int cell = (typeFood == -2) ? 1 : 2;
    int fg = (_key == 'd' || _key == 's') ? -1 : 1;
    for (int i = 0; i < cell; ++i) {
        auto tail = _cors.front();
        if (_key == 'a' || _key == 'd') {
            _cors.push_front({tail.y_dis, tail.x_dis + (_size_block * fg), tail.y_arr, tail.x_arr + fg});
        } else if (_key == 'w' || _key == 's') {
            _cors.push_front({tail.y_dis + (_size_block * fg), tail.x_dis, tail.y_arr + fg, tail.x_arr});
        }
    }
    for (auto fIt = Food::_coorOnMap.begin(); cell == 2  && fIt != Food::_coorOnMap.end(); fIt++){
        if (Mmap::getInstance().getValueFromMap(fIt->first, fIt->second) != -1){
            Mmap::getInstance().setValueInMap(0, fIt->first, fIt->second);
        }
        fIt->first = 0;
        fIt->second = 0;
    }
}

void Logic::changeSize(int n) {
    _size_block = g_weight / 90;
    _rect.w = _rect.h = _size_block;
    for (auto it = _cors.begin(); it != _cors.end(); it++) {
        (*it).x_dis = (n > 0) ? ((*it).x_dis * 2) : ((*it).x_dis / 2);
        (*it).y_dis = (n > 0) ? ((*it).y_dis * 2) : ((*it).y_dis/ 2);
    }
}

Logic::~Logic() {}
