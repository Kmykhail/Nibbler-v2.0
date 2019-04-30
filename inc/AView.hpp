//
// Created by kmykhailenko on 31.12.18.
//

#pragma once

#include <vector>
#include <iostream>

class AView {
public:
    virtual ~AView(){}
    virtual void    init() = 0;
    virtual void    initMap(int) = 0;
    virtual int     catchHook() = 0;
    virtual void     render() = 0;
    virtual void    drawMenu(void*, void*, int) = 0;
    virtual void    renderClear() = 0;
    virtual void    drawMap() = 0;
    virtual void    drawSnake(void*, int) = 0;
    virtual void    drawFood(void*) = 0;
    virtual void    drawBigFood(void*) = 0;
    virtual void    drawInterface(std::string, int) = 0;
    virtual void    drawTimeBigFood(int) = 0;
    virtual void    drawChangeMap(int) = 0;
    virtual uint32_t     getTicks() = 0;
    virtual void    delay(int) = 0;
    virtual void    cleanWindow() = 0;
    virtual void    drawGameOver(int) = 0;
};
