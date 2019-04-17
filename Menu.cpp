//
// Created by Kostiantyn MYKHAILENKO on 2019-01-19.
//

#include "Menu.hpp"
#include "global.h"
#include "Mmap.hpp"
#include "Game_Obj.hpp"

int _numMap;

Menu::Menu() noexcept {
    _size_block = g_weight / 90 + 20;//50 is scale for arrow
    _rectA.w = _rectA.h = _size_block;//rect for Arrow

    /**********RECT FOR BUTTON********/
    _rectB.h = _size_block;
    _rectB.w = _size_block * 4;

    _numButton = 1;//number of button
    _typeMenu = 1;//flag for 1 is Start_menu, 2 is Escape_Menu, 3 is Pause_menu
    _select = true;//flag for select menu
    _selectMap = false;
}

void Menu::initMenu() {
    _rectA.x = g_weight / 2 - (_size_block * 4) - 10;// position of arrow x
    _rectA.y = g_height / 2 - (_size_block * 3) - 10;// position of arrow y

    _rectB.x = g_weight / 2 - (_size_block * 2) - 10;
    _rectB.y = _rectA.y; //button must be on the same level with arrow
    _numButton = 1;

    Game_Obj::viev->drawMenu(&_rectA, &_rectB, _typeMenu);
    Game_Obj::viev->render();
}

bool Menu::changebutton() {
    if (_selectMap == true) {
        changeMap();
        return true;
    }
    if (_key == 36){//enter, which mean that player chosed number of players
        _key = 0;
        if ((_typeMenu == 3 && _numButton == 3) || (_typeMenu != 3 && _numButton == 4)){
            return false;
        }
        if (_numButton == 1 && _typeMenu !=3){
            _numMap = 1;
            _selectMap = true;
            changeMap();
            return true;
        }
         _typeMenu = 1;
        _select = false;
        return true;
    }
    moveArrow();
    Game_Obj::viev->drawMenu(&_rectA, &_rectB, _typeMenu);
    _key = 0;
    return true;
}

void Menu::changeMap() {
        Game_Obj::viev->renderClear();
        Game_Obj::viev->drawChangeMap(_numMap);
        if (_key == 124 && _numMap != 2){//125 down
            _numMap += 1;
        }
        else if (_key == 123 && _numMap != 1){//126 up
           _numMap--;
        }
        if (_key == 36) {
            Mmap::getInstance().setMap(_numMap);
            Game_Obj::viev->initMap(_numMap);
            _selectMap = false;
            _select = false;
        }
}
void Menu::moveArrow() {
    if (_key == 125 && _numButton != 4){//125 down
        _rectA.y += (_typeMenu == 3 && _numButton == 3) ? 0 :  _rectA.h + 10;
        _numButton += (_typeMenu == 3 && _numButton == 3) ? 0 : 1;
        Game_Obj::music->playButton();
    }
    else if (_key == 126 && _numButton != 1){//126 up
        _rectA.y -=  _rectA.h + 10;
        _numButton--;
        Game_Obj::music->playButton();
    }
}

void Menu::escapeDialog() {
    _typeMenu = 2;
    _select = true;
}

void Menu::pauseDialog() {
    _typeMenu = 3;
    _select = true;
}

bool Menu::runningMenu() const { return _select;}
void Menu::setKey(int key) {_key = key;}

void Menu::changeSize() {
    _size_block = g_weight / 90 + 20;
    _rectA.w = _rectA.h = _size_block;

    /**********RECT FOR BUTTON********/
    _rectB.h = _size_block;
    _rectB.w = _size_block * 4;
    _rectA.x = g_weight / 2 - (_size_block * 4) - 10;// position of arrow x
    _rectA.y = g_height / 2 - (_size_block * 3) - 10;// position of arrow y

    _rectB.x = g_weight / 2 - (_size_block * 2) - 10;
    _rectB.y = _rectA.y; //button must be on the same level with arrow
    _numButton = 1;
}

Menu::~Menu() {}