//
// Created by Tetiana PIVEN on 2019-04-07.
//
#pragma once

#include "SFML/Audio.hpp"
#include "Music.hpp"

class Music_lib: public Music {
public:
    Music_lib();

    virtual ~Music_lib();

    void init() override;
    void playMusic() override;
    void playEat() override;
    void playGame_over() override;
    void playCrash() override;
    void playButton() override;
    void stopMusic() override;

private:
    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;
    sf::SoundBuffer buffer4;
    sf::Sound eating;
    sf::Sound crash;
    sf::Sound button;
    sf::Sound game_over;
    sf::Music music;
};


