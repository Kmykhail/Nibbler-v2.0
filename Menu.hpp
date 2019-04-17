//
// Created by Kostiantyn MYKHAILENKO on 2019-01-19.
//

#pragma once

#include "header.h"

class Menu {
public:
    Menu() noexcept;
    ~Menu();
    void    initMenu();
    void    setKey(int key);
    bool    runningMenu() const;
    bool    changebutton();
    void    escapeDialog();
    void    pauseDialog();
    void    changeSize();
    void    changeMap();
private:
    int _numButton;//number of button
    char _key;//w,a,s,d
    int _size_block;
    t_scr _rectA;//struct for render Arrow texture
    t_scr _rectB;//struct for render Button texture
    bool _select;//flag for select menu
    bool _selectMap;
    int  _typeMenu;//flag for 1 is Start_menu, 2 is Escape_Menu, 3 is Pause_menu
    void moveArrow();
};
