//
// Created by kmykhailenko on 31.12.18.
//
#pragma once
#include <map>
#include <list>
#include <tuple>
#include "header.h"

using lst = std::list<t_coor>;

class Logic {
public:
    explicit Logic() noexcept;
    ~Logic();
    void    move();
    bool    runningGame() const;
    void    setKey(int key);
    void    init(int);
    void    restart();
    void    changeSize(int);
private:
    lst _cors;
    int _pl;
    char _key;
    int _size_block;
    t_scr _rect;
    bool _playGame;
    void    updateHead(t_coor&);
    void    crash();
    void    grow(int typeFood);
    Logic(const Logic&) = delete;
    Logic&operator=(const Logic&) = delete;
    Logic(Logic &&) = delete;
    Logic& operator=(Logic&&) = delete;
};

