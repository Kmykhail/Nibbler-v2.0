//
// Created by Tetiana PIVEN on 2019-04-07.
//

#include "Music_lib.hpp"
#include <thread>
#include <chrono>

Music_lib::Music_lib() {

}

Music_lib::~Music_lib() {

}

void Music_lib::init() {
   if(!music.openFromFile("Picture/s.wav"))
   {
       std::cout << "ERRor" << std::endl;
        exit(1);
   }
    if( !buffer.loadFromFile("Picture/eat.wav")){
        std::cout << "ERRorghgh" << std::endl;
        exit(1);
    }
    eating.setBuffer(buffer);
    eating.setVolume(200);
    if( !buffer2.loadFromFile("Picture/d.wav")){
        std::cout << "ERRorghgh" << std::endl;
        exit(1);
    }
    button.setBuffer(buffer2);
    button.setVolume(40);

    if( !buffer3.loadFromFile("Picture/t.wav")){
        std::cout << "ERRorghgh" << std::endl;
        exit(1);
    }
    crash.setBuffer(buffer3);
    crash.setVolume(200);
    if( !buffer4.loadFromFile("Picture/game_over3.wav")){
        std::cout << "ERRorghgh" << std::endl;
        exit(1);
    }
    game_over.setBuffer(buffer4);
    game_over.setVolume(20);
}

void Music_lib::playMusic() {
    music.setVolume(10);
    music.play();
    music.setLoop(true);
}

void Music_lib::playEat() {
    eating.play();
}

void Music_lib::playGame_over() {
    game_over.play();
}

void Music_lib::playButton() {
    button.play();
}

void Music_lib::playCrash() {
    crash.play();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Music_lib::stopMusic() {
    music.stop();
}


extern "C"  Music* getInstance() {
    return new Music_lib();
}

extern "C" void		destroy_object(Music_lib *gui) {
    delete gui;
}
