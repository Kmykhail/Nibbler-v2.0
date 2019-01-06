//
// Created by kmykhailenko on 31.12.18.
//

//class INibDisplay{
//public:
//    virtual void init() = 0;//инициализация Любой либы
//    virtual void getEvent() = 0;//ловим хуки от клавиш
//    virtual void updateGameDate() = 0;//обновляем дату по хукам
//    virtual void refreshDisplay() = 0;//перерисовка
//    virtual void stop() = 0;//конец игры ???
//};

//#ifdef _WIN32 // note the underscore: without it, it's not msdn official!
//    // Windows (x64 and x86)
//#elif __unix__ // all unices, not all compilers
//    // Unix
//#elif __linux__
//    // linux
//#elif __APPLE__
//    // Mac OS, not sure if this is covered by __posix__ and/or __unix__ though...
//#endif

#pragma once

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#elif __APPLE__
#include "SDL.h"
#include "SDL_image.h"
#endif

#include <vector>
#include <iostream>

class AView {
public:
    ~AView(){}
    virtual void    init() = 0;//инит окна и прочего
    virtual int     catchHook() = 0; //ловим хуки от клавиш
    virtual void    render() = 0;//рисуем
    virtual void    drawMap() = 0;
    virtual void    drawSnake(void*, int) = 0;
    virtual void    drawFood(void*) = 0;
    virtual uint32_t     getTicks() = 0;
    virtual void    delay(int) = 0;
    virtual void    cleanWindow() = 0;
};