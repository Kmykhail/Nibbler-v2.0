//
// Created by kmykhailenko on 31.12.18.
//

#include "Game_Obj.hpp"
#include "Logic.hpp"
#include "Mmap.hpp"
#include <ctime>
#include <thread>
#include <chrono>
#include "SDL_lib.hpp"
#include <vector>
#include "global.h"

Game_Obj::Game_Obj() {}

Game_Obj::~Game_Obj() {
    std::cout << "!!!" << std::endl;
    delete _inst;
}

Game_Obj* Game_Obj::_inst = nullptr;

Game_Obj* Game_Obj::getInstance() {
    if (!_inst){
        _inst = new Game_Obj;
    }
    return _inst;
}

void Game_Obj::init() {
    Logic logic(1);
    std::cout << "wwork" << std::endl;
    std::vector<AView*> lib_ptr = {&SDL_lib::getInstance()};//, SFML_lib::getInstance, ALLEGRO_lib::
    lib_ptr.front()->init();
    while(logic.running()){
        lib_ptr[g_lib - 1]->drawMap();
        logic.move();
        lib_ptr[g_lib - 1]->render();
        std::cout << "------" << std::endl;
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game_Obj::handleEvent() {}
void Game_Obj::update() {}
void Game_Obj::render() {}