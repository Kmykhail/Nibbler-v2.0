//
// Created by Tetiana PIVEN on 2019-01-27.
//

#pragma once

#include <chrono>
#include "header.h"

class Interface {
public:
    static Interface* getInstance();
    void    initInterface();
    void    changeTimeAndScore();
    void    setScore(int plus);
    int     getScore();
    void    restart();
private:
    static Interface *_inst;
    int score;
    int time;
    std::chrono::time_point<std::chrono::system_clock> start;
    Interface();
    ~Interface();
    Interface(Interface &&) = delete;
    Interface(const Interface &) = delete;
    Interface& operator=(const Interface &) = delete;
    Interface& operator=(Interface &&) = delete;
};