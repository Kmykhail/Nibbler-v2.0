//
// Created by Kostiantyn MYKHAILENKO on 2019-01-19.
//

#pragma once

#include "header.h"

class Menu {
public:
    explicit Menu() noexcept;
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
    int _numButton;
    char _key;
    int _size_block;
    t_scr _rectA;
    t_scr _rectB;
    bool _select;
    bool _selectMap;
    int  _typeMenu;
    void moveArrow();
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    Menu(Menu&&) = delete;
    Menu& operator=(Menu&&) = delete;
};
