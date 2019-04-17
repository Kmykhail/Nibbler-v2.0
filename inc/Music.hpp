//
// Created by Tetiana PIVEN on 2019-04-07.
//

#pragma once
#include <vector>
#include <iostream>

class Music {
public:
    Music() {}
    ~Music() {}
    virtual void init() = 0;
    virtual void playMusic() = 0;
    virtual void playEat() = 0;
    virtual void playGame_over() = 0;
    virtual void playCrash() = 0;
    virtual void playButton() = 0;
    virtual void stopMusic() = 0;
};
