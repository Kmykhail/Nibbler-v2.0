//
// Created by kmykhailenko on 02.01.19.
//

#include "SDL_lib.hpp"
#include "global.h"
#include <unistd.h>
#include "Mmap.hpp"
#define CREATE_TEXTURE(str) TextureManager::getInstance().LoadTexture(str)

const char tail_path[] = "/Picture/dirt.png";//TODO create many picture like: tail_16x16, tail_8x8
const char body_path[] = "/Picture/grass_bloc_mod.png";
const char head_path[] = "/Picture/dirt_1.png";
const char map_1[] = "/Picture/map_1.png";
const char lilFood[] = "/Picture/solid.png";
const char buttonSingle_path[] = "/Picture/button1.png";
const char buttonMulti_path[] = "/Picture/button2.png";
extern const char buttonOption_path[] = "/Picture/options.png";
extern const char buttonContinue_path[] = "/Picture/continue.png";
extern const char buttonExit_path[] = "/Picture/exit.png";
const char arrow_path[] = "/Picture/arrow_path.png";

SDL_Renderer* SDL_lib::renderer = nullptr;
SDL_Window*     SDL_lib::_window = nullptr;
SDL_Texture*    SDL_lib::_textureMap = nullptr;
SDL_Texture*    SDL_lib::_textureFood = nullptr;
SDL_Texture*    SDL_lib::_textureArrow = nullptr;

SDL_lib::SDL_lib() {}
SDL_lib::~SDL_lib() {}
SDL_lib& SDL_lib::getInstance() {
    static SDL_lib instance;
    return instance;
}

void SDL_lib::init() {
    /************INIT WINDOW************/
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Trouble with init SDL" << std::endl;
        exit(-1);
    }
    _window = SDL_CreateWindow(
            "Jörmungandr",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            g_weight,
            g_height + HEIGHT_SCOREBOARD,
            SDL_WINDOW_SHOWN
            );
    if (!_window){
        std::cerr << "Error Window: " << &SDL_Error << std::endl;
        exit(-1);
    }
    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Trouble wih render" << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);//BAG NOT WORKING
    char path[4096];
    _dir = getwd(path);
    size_t  n = _dir.rfind('/');
    //_dir.resize(n); //TODO investigate PATH of PICTURES
    /************INIT TEXTURE FOR BUTTON***********/
    _buttonTexture = {{"single", CREATE_TEXTURE((_dir + buttonSingle_path).c_str())}, {"multi", CREATE_TEXTURE((_dir + buttonMulti_path).c_str())},
                      {"continue", CREATE_TEXTURE((_dir + buttonContinue_path).c_str())}, {"option", CREATE_TEXTURE((_dir + buttonOption_path).c_str())},
                      {"exit", CREATE_TEXTURE((_dir + buttonExit_path).c_str())}};
    if (_buttonTexture.empty()){
        std::cerr << "textureButton not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR ARROW************/
    std::string toto = _dir + arrow_path;
    SDL_Surface *qw = IMG_Load((_dir + arrow_path).c_str());
    _textureArrow = CREATE_TEXTURE((_dir + arrow_path).c_str());
    if (!_textureArrow){
        std::cerr << "textureArrow not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR MAP**************/
    _textureMap = CREATE_TEXTURE((_dir + map_1).c_str());
    if (!_textureMap){
        std::cerr << "textuteMap not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR SNAKE************/
    _snakeTexture = {{0, CREATE_TEXTURE((_dir + tail_path).c_str())}, {1, CREATE_TEXTURE((_dir + body_path).c_str())},
                     {2, CREATE_TEXTURE((_dir + head_path).c_str())}};
    if (_snakeTexture.empty()){
        std::cerr << "textureSnake not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR FOOD************/
    std::cout << "lilFood" << lilFood << std::endl;
    std::cout << "path: " << _dir  << lilFood << std::endl;
    _textureFood = CREATE_TEXTURE((_dir + lilFood).c_str());
    if (!_textureFood){
        std::cerr << "textuteFood not exist" << std::endl;
        exit(1);
    }
}

int SDL_lib::catchHook(){
    SDL_PollEvent(&_event);
    if (_event.type == SDL_QUIT){
        std::cout << "EXIT" << std::endl;
        return -1;
    }
    if (_event.type == SDL_KEYDOWN){
        switch (_event.key.keysym.sym){
            case SDLK_ESCAPE:
                std::cout << "EXIT" << std::endl;
                return -1;
            case SDLK_w:
                std::cout << "w" << std::endl;
                return 'w';
            case SDLK_s:
                std::cout << "s" << std::endl;
                return 's';
            case SDLK_d:
                std::cout << "d" << std::endl;
                return 'd';
            case SDLK_a:
                std::cout << "a" << std::endl;
                return 'a';
            case SDLK_SPACE:
                return ' ';
            case SDLK_UP:
                return 126;
            case SDLK_DOWN:
                return 125;
            case SDLK_LEFT:
                return 123;
            case SDLK_RIGHT:
                return 124;
            case SDLK_RETURN:
                return 36;//enter
            default:
                return 0;
        }
    }
    return 0;
}

uint32_t SDL_lib::getTicks() {
    return SDL_GetTicks();
}

void SDL_lib::delay(int time) {
    SDL_Delay(time);
}

void SDL_lib::render() {
    SDL_RenderPresent(renderer);
}

void SDL_lib::drawMenu(void* rectA, void* rectB, int typeMenu) {
    _mcrR = *reinterpret_cast<SDL_Rect*>(rectA);
    /***********ADD ARROW TEXTURE***********/
    SDL_RenderCopy(renderer, _textureArrow, nullptr, &_mcrR);//render arrow
    /***********ADD BUTTON TEXTURE***********/
    _mcrR = *reinterpret_cast<SDL_Rect*>(rectB);
    if (typeMenu == 3){
        SDL_RenderCopy(renderer, _buttonTexture["continue"], nullptr, & _mcrR);
        _mcrR.y += _mcrR.h + 10;// distance between continue and multi option
        SDL_RenderCopy(renderer, _buttonTexture["option"], nullptr, &_mcrR);
        _mcrR.y += _mcrR.h + 10;// distance between option and multi exit
        SDL_RenderCopy(renderer, _buttonTexture["exit"], nullptr, &_mcrR);
    }
    else {
        SDL_RenderCopy(renderer, _buttonTexture["single"], nullptr, &_mcrR);//single player
        _mcrR.y += _mcrR.h + 10;// distance between single and multi button
        SDL_RenderCopy(renderer, _buttonTexture["multi"], nullptr, &_mcrR);//multi player
        _mcrR.y += _mcrR.h + 10;// distance between multi and option
        SDL_RenderCopy(renderer, _buttonTexture["option"], nullptr, &_mcrR);
        _mcrR.y += _mcrR.h + 10;// distance between option and exit
        SDL_RenderCopy(renderer, _buttonTexture["exit"], nullptr, &_mcrR);
    }
}

void SDL_lib::drawMap() {
    _scrR.y = HEIGHT_SCOREBOARD;
    _scrR.x = WEIGHT_SCOREBOARD;
    _scrR.w = g_weight;
    _scrR.h = g_height;
    SDL_RenderCopy(renderer, _textureMap, nullptr, &_scrR);
}

void SDL_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head
    _scrR = *reinterpret_cast<SDL_Rect*>(rect);
    SDL_RenderCopy(renderer, _snakeTexture[b_block], nullptr, &_scrR);
}

void SDL_lib::drawFood(void* rect) {
    _fcrR = *reinterpret_cast<SDL_Rect*>(rect);
    SDL_RenderCopy(renderer, _textureFood, nullptr, &_fcrR);
}

void SDL_lib::renderClear() {
    SDL_RenderClear(renderer);
}

void SDL_lib::cleanWindow() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
