//
// Created by kmykhailenko on 31.12.18.
//

#include "Game_Obj.hpp"
#include "Logic.hpp"
#include "Mmap.hpp"
#include "Interface.hpp"
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include "global.h"
#include <ctime>
#include <unistd.h>
#include <mutex>

extern int const FPS = 60;
uint32_t  frameStart;
int frameTime;
unsigned Game_Obj::_frameDelay = 4000 / FPS;

Game_Obj::Game_Obj() {}

Game_Obj::~Game_Obj() {
    std::cout << "Start Game_Obj::~Game_Obj" << std::endl;
    void    (*destroy_gui)(AView *);
    void    (*destroy_music)(Music*);
    destroy_gui = (void (*)(AView *))dlsym(dl_lib, "destroy_object");
    destroy_gui(viev);
    if (this->dl_lib != NULL) {
        dlclose(this->dl_lib);
    }

    destroy_music = (void (*)(Music *))dlsym(dl_music, "destroy_object");
    destroy_music(music);
    if (this->dl_music != NULL) {
        dlclose(this->dl_music);
    }
    std::cout << "End Game_Obj::~Game_Obj" << std::endl;
}

void *Game_Obj:: dl_lib = nullptr;
void *Game_Obj:: dl_music = nullptr;
AView*  Game_Obj::viev = nullptr;
Music*  Game_Obj::music = nullptr;

bool Game_Obj::menu() {
    std::cout << "Start Game_Obj::menu" << std::endl;
    int const frameDealy = 4000 / FPS;
    while(_menu.runningMenu()){
        viev->renderClear();
        frameStart = viev->getTicks();
        if (handleEvent() == -1){
            return false;
        }
        if (!_menu.changebutton()){
            return false;
        }
        frameTime = viev->getTicks() - frameStart;
        if (frameDealy > frameTime && frameTime >= 0){
            viev->delay(frameDealy - frameTime);
        }
        viev->render();
    }
    music->playMusic();
    std::cout << "End Game_Obj::menu" << std::endl;
    return true;
}

void Game_Obj::addMusicLib() {
    std::cout << "Start Game_Obj::addMusicLib" << std::endl;
    Music*		(*getInstance)();

    dl_music = dlopen("../lib_Music.dylib", RTLD_LAZY);
//    dl_music = dlopen("lib_Music.dylib", RTLD_LAZY);
    if (!dl_music) {
        std::cerr << "dl_error" << std::endl;
        exit(1);
    }
    getInstance = reinterpret_cast<Music*(*)()> (dlsym(dl_music, "getInstance"));
    if (!getInstance) {
        std::cerr << "dl_error" << std::endl;
        exit(1);
    }
    music = getInstance();
    std::cout << "End Game_Obj::addMusicLib" << std::endl;

}

void Game_Obj::addNewSharedLib() {
    std::cout << "Start Game_Obj::addNewSharedLib" << std::endl;
    AView*		(*getInstance)(int, int);
    void	(*destroy_gui)(AView *);

    if (dl_lib != NULL) {
        destroy_gui = (void (*)(AView *))dlsym(dl_lib, "destroy_object");
        destroy_gui(viev);
        dlclose(dl_lib);
        dl_lib = NULL;
    }

    dl_lib = dlopen(library[g_lib - 1].c_str(), RTLD_LAZY);
    if (!dl_lib) {
        std::cerr << "dl_error" << std::endl;
        exit(1);
    }
    getInstance = reinterpret_cast<AView*(*)(int, int)> (dlsym(dl_lib, "getInstance"));
    if (!getInstance) {
        std::cerr << "Error getInstance" << std::endl;
        exit(1);
    }
    viev = getInstance(g_weight, g_height);
    std::cout << "End Game_Obj::addNewSharedLib" << std::endl;
}

void Game_Obj::init() {
    std::cout << "Start Game_Obj::init" << std::endl;
    library[0] = "../libSDL.dylib";
    library[1] = "../libSFML.dylib";
    library[2] = "../libGL.dylib";
//    library[0] = "libSDL.dylib";
//    library[1] = "libSFML.dylib";
//    library[2] = "libGL.dylib";
    addNewSharedLib();
    addMusicLib();
    music->init();
    viev->init();
    _menu.initMenu();
    if (!menu()){
        viev->cleanWindow();
        return;
    }

    Interface::getInstance().initInterface();

    viev->drawMap();
    _logic.init(1);

    Interface::getInstance().changeTimeAndScore();

    _food.updateFood();
    viev->render();
    main_loop();
    std::cout << "End Game_Obj::init" << std::endl;
}

void Game_Obj::main_loop() {
    std::cout << "Start Game_Obj::main_loop" << std::endl;
    music->playMusic();
    while(1){
        viev->renderClear();
        frameStart = viev->getTicks();
        if (!_logic.runningGame()){
            music->stopMusic();
            if (!escapeLogic()){
                break;
            }
        }
        else if (!action()){
                break;
        }
        frameTime = viev->getTicks() - frameStart;
        if (static_cast<int>(_frameDelay) > frameTime && frameTime >= 0){
            viev->delay(_frameDelay - frameTime);
        }
    }
    viev->cleanWindow();
    std::cout << "End Game_Obj::main_loop" << std::endl;
}

bool Game_Obj::escapeLogic() {
    std::cout << "Start Game_Obj::escapeLogic" << std::endl;
    int const frameDealy = 4000 / FPS;
    _menu.escapeDialog();
    _mapInit = false;
    _logic.restart();
    _food.restart();
    music->playGame_over();
    while(1){
        int key = handleEvent();
        if (key == 32){
            break;
        }
        if (key == -1){
            return false;
        }
        viev->renderClear();
        viev->drawGameOver(Interface::getInstance().getScore());
        frameTime = viev->getTicks() - frameStart;
        if (frameDealy > frameTime && frameTime >= 0){
            viev->delay(frameDealy - frameTime);
        }
        viev->render();
    }
    if (!menu()){
        return false;
    }
    Interface::getInstance().restart();
    music->playMusic();
    std::cout << "End Game_Obj::escapeLogic" << std::endl;
    return true;
}

bool Game_Obj::pauseLogic() {
    std::cout << "Start Game_Obj::pauseLogic" << std::endl;
    music->stopMusic();
    _menu.pauseDialog();
    std::cout << "End Game_Obj::pauseLogic" << std::endl;
    return menu();
}

bool Game_Obj::action() {
    std::cout << "Start Game_Obj::action" << std::endl;
    int key = handleEvent();
    if (key == -1 || (key == ' ' && !pauseLogic())){
        std::cout << "End Game_Obj::action" << std::endl;
        return false;
    }
    update();
    viev->render();
    key = handleEvent();
    if (key == -1 || (key == ' ' && !pauseLogic())){
        std::cout << "End Game_Obj::action" << std::endl;
        return false;
    }
    std::cout << "End Game_Obj::action" << std::endl;
    return true;
}

void Game_Obj::switchLib(int symb) {
    std::cout << "Start Game_Obj::switchLib" << std::endl;
    viev->cleanWindow();
    if (symb == 2) {
        g_height *=2;
        g_weight *=2;
        HEIGHT_SCOREBOARD = g_weight / 14;
        _logic.changeSize(1);
        _food.changeSize(1);
        _menu.changeSize();
    }
    if ((symb == 1 || symb == 3) && g_lib == 2)
    {
        g_height /=2;
        g_weight /=2;
        HEIGHT_SCOREBOARD = g_weight / 14;
        _logic.changeSize(-1);
        _food.changeSize(-1);
        _menu.changeSize();
    }
    g_lib = symb;
    addNewSharedLib();
    viev->init();
    if (_mapInit) {
        viev->initMap(_numMap);
    }
    std::cout << "End Game_Obj::switchLib" << std::endl;
}


int Game_Obj::handleEvent() {
    std::cout << "Start Game_Obj::handleEvent" << std::endl;
    int symb = viev->catchHook();
    if (symb == -1) {
        return symb;
    }
    if ((symb == 1 || symb == 2 || symb == 3) && symb != g_lib){
          switchLib(symb);
    }
    else if (symb != 0) {
        (!_menu.runningMenu() && symb != ' ') ? _logic.setKey(symb) : _menu.setKey(symb);
    }
    std::cout << "End Game_Obj::handleEvent" << std::endl;
    return symb;
}

void Game_Obj::update() {
    std::cout << "Start Game_Obj::update" << std::endl;
    viev->drawMap();
    _logic.move();
    Interface::getInstance().changeTimeAndScore();
   _food.updateFood();
    std::cout << "End dGame_Obj::update" << std::endl;
}
