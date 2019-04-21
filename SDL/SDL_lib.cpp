//
// Created by kmykhailenko on 02.01.19.
//

#include "SDL_lib.hpp"
#include "global.h"
#include <unistd.h>
#include "Mmap.hpp"
#include <stdio.h>
#define CREATE_TEXTURE(str) TextureManager::getInstance().LoadTexture(str)
#define CREATE_TEXTURETEXT(str, color, tcrR) TextureManager::getInstance().LoadTextureText(str, color, tcrR)

const char tail_path[] = "/Picture/snake_tails.png";
const char body_path[] = "/Picture/snake_body.png";
const char head_path[] = "/Picture/snake_head.png";
const char map_1[] = "/Picture/map_1.png";
const char map_2[] = "/Picture/map_2.png";
const char lilFood[] = "/Picture/lilfood.png";
const char bigFood[] = "/Picture/bigfood.png";
const char buttonSingle_path[] = "/Picture/button1.png";
const char buttonMulti_path[] = "/Picture/button2.png";

const char lineFood_path[] = "/Picture/lineTimeFood.png";

extern const char buttonOption_path[] = "/Picture/options.png";
extern const char buttonContinue_path[] = "/Picture/continue.png";
extern const char buttonExit_path[] = "/Picture/exit.png";
const char arrow_path[] = "/Picture/arrow_path.png";
const char gameOver_path[] = "/Picture/gameOver.png";
const char font_path[] = "/Picture/ArialItalic.ttf";

SDL_Renderer* SDL_lib::renderer = nullptr;
SDL_Window*     SDL_lib::_window = nullptr;
SDL_Texture*    SDL_lib::_textureMap = nullptr;
SDL_Texture*    SDL_lib::_map1 = nullptr;
SDL_Texture*    SDL_lib::_map2 = nullptr;
SDL_Texture*    SDL_lib::_textureFood = nullptr;
SDL_Texture*    SDL_lib::_textureBigFood = nullptr;
SDL_Texture*    SDL_lib::_textureArrow = nullptr;
SDL_Texture*    SDL_lib::_textureText = nullptr;
SDL_Texture*     SDL_lib::_textureLine = nullptr;
SDL_Texture*    SDL_lib::_textureGameOver = nullptr;
SDL_Texture*    SDL_lib::_textureScore = nullptr;
TTF_Font*       SDL_lib::_font = nullptr;
TTF_Font*       SDL_lib::_game_over = nullptr;


SDL_lib::SDL_lib() {}

SDL_lib::SDL_lib(int weight, int height) {

    g_weight = weight;
    g_height = height;
    HEIGHT_SCOREBOARD = g_weight / 14;
    SizeFont = HEIGHT_SCOREBOARD / 4;

}

SDL_lib::~SDL_lib() {
    std::cout << "CLOSE LIB SDL" << std::endl;
}


void SDL_lib::init() {
    /************INIT WINDOW************/
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Trouble with init SDL" << std::endl;
        exit(-1);
    }
    _window = SDL_CreateWindow(
            "Nibbler",
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//BAG NOT WORKING
    SDL_RenderClear(renderer);
    char path[4096];
    _dir = getwd(path);

    /************INIT TEXTURE FOR BUTTON***********/
    _buttonTexture = {{"single", CREATE_TEXTURE((_dir + buttonSingle_path).c_str())}, {"multi", CREATE_TEXTURE((_dir + buttonMulti_path).c_str())},
                      {"continue", CREATE_TEXTURE((_dir + buttonContinue_path).c_str())}, {"option", CREATE_TEXTURE((_dir + buttonOption_path).c_str())},
                      {"exit", CREATE_TEXTURE((_dir + buttonExit_path).c_str())}};
    if (_buttonTexture.empty()){
        std::cerr << "textureButton not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR ARROW************/
    _textureArrow = CREATE_TEXTURE((_dir + arrow_path).c_str());
    if (!_textureArrow){
        std::cerr << "textureArrow not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR MAP**************/

    _map1 = CREATE_TEXTURE((_dir + map_1).c_str());
    if (!_map1){
        std::cout << "Path: " << _dir + map_1 << std::endl;
        std::cerr << "textuteMap1 not exist" << std::endl;
        exit(1);
    }
    _map2 = CREATE_TEXTURE((_dir + map_2).c_str());
    if (!_map2){
    std::cerr << "textuteMap2 not exist" << std::endl;
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
    _textureFood = CREATE_TEXTURE((_dir + lilFood).c_str());
    _textureFood = CREATE_TEXTURE((_dir + lilFood).c_str());
    if (!_textureFood){
        std::cerr << "textuteFood not exist" << std::endl;
        exit(1);
    }

    _textureBigFood = CREATE_TEXTURE((_dir + bigFood).c_str());
    if (!_textureBigFood){
        std::cerr << "textuteBigFood not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR LINE TIME OF SURP FOOD************/
    _textureLine = CREATE_TEXTURE((_dir + lineFood_path).c_str());
    if (!_textureLine){
        std::cerr << "textureLine not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE GAME OVER************/
    _textureGameOver = CREATE_TEXTURE((_dir + gameOver_path).c_str());
    if (!_textureGameOver){
        std::cerr << "textureGameOver not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR FONT************/
    if (TTF_Init() < 0){
        std::cout << TTF_GetError() << std::endl;
        exit(-1);
    }

    if (!(_font = TTF_OpenFont((_dir + font_path).c_str(), SizeFont))){//TODO change size font on variable
        std::cerr << "textureText not exist" << std::endl;
        exit(1);
    }
    _textColor = {255, 0, 0, 0};//color red
    if (!(_game_over = TTF_OpenFont((_dir + font_path).c_str(), (HEIGHT_SCOREBOARD/ 3)))){
        std::cerr << "text Game Over not exist" << std::endl;
        exit(1);
    }
    _tColor = {107,142,35, 0};

}

void SDL_lib::initMap(int n) {
    if (n == 1){
        _textureMap = CREATE_TEXTURE((_dir + map_1).c_str());
        if (!_textureMap){
            std::cerr << "textuteMap not exist" << std::endl;
            exit(1);
        }
    }
    else if(n == 2) {
        _textureMap = CREATE_TEXTURE((_dir + map_2).c_str());
        if (!_textureMap){
            std::cerr << "textuteMap not exist" << std::endl;
            exit(1);
        }       
    }   
}


int SDL_lib::catchHook(){
    while(SDL_PollEvent(&_event) != 0) {
        if (_event.type == SDL_QUIT) {
            std::cout << "EXIT" << std::endl;
            return -1;
        }
        if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    std::cout << "PAUSE" << std::endl;
                    return ' ';
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
                case SDLK_1://change current lib on SDL
                    return 1;
                case SDLK_2://change current lib on SFML
                    return 2;
                case SDLK_3://change current lib on ALLEGRO
                    return 3;
                default:
                    return 0;
            }
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
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear(renderer);
     _scrR.y = HEIGHT_SCOREBOARD;
    _scrR.x = 0;
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

void SDL_lib::drawBigFood(void* rect) {
    _fcrR = *reinterpret_cast<SDL_Rect *>(rect);
    SDL_RenderCopy(renderer, _textureBigFood, nullptr, &_fcrR);
}

void SDL_lib::drawInterface(std::string clock, int score) {
    /***************DRAW CLOCK****************/
    _textureText = CREATE_TEXTURETEXT(clock.c_str(), _textColor, _tcrR);
    _tcrR.x = 50;
    _tcrR.y = HEIGHT_SCOREBOARD/2;
    SDL_RenderCopy(renderer, _textureText, nullptr, &_tcrR);
    /***************DRAW SCORE****************/
    _textureText = CREATE_TEXTURETEXT(("Score:   " + std::to_string(score)).c_str(), _textColor, _tcrR);
    _tcrR.x = g_weight/3;
    _tcrR.y = HEIGHT_SCOREBOARD/2;
    SDL_RenderCopy(renderer, _textureText, nullptr, &_tcrR);
}

void SDL_lib::drawTimeBigFood(int time) {
    /***************DRAW LINE TIME FOR SURP FOOD****************/
    _lcrR = {(g_weight / 3) * 2, HEIGHT_SCOREBOARD / 2, time, SizeFont - 10};
    SDL_RenderCopy(renderer, _textureLine, nullptr, &_lcrR);
}

void SDL_lib::renderClear() {
    SDL_RenderClear(renderer);
}

void SDL_lib::drawGameOver(int score) {
    _gcrR = {(g_weight / 3), g_height / 3, g_weight / 3, g_height / 3};
    SDL_RenderCopy(renderer, _textureGameOver, nullptr, &_gcrR);
    _textureScore = CREATE_TEXTURETEXT(("SCORE   " + std::to_string(score)).c_str(), _tColor, _tcrR);
    _tcrR.x = g_weight/2 - (HEIGHT_SCOREBOARD / 3) * 2;
    _tcrR.y = (g_height / 3) * 2;
    SDL_RenderCopy(renderer, _textureScore, nullptr, &_tcrR);

    _textureScore = CREATE_TEXTURETEXT("Please, press space key", _tColor, _tcrR);
    _tcrR.x = g_weight / 2 - (HEIGHT_SCOREBOARD + (HEIGHT_SCOREBOARD / 3));
    _tcrR.y = g_height - HEIGHT_SCOREBOARD;
    SDL_RenderCopy(renderer, _textureScore, nullptr, &_tcrR);

}
void SDL_lib::drawChangeMap(int n) {
    (void)n;
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear(renderer);

    _gcrR = {g_weight / 4, g_height / 3, 180, 134};
    SDL_RenderCopy(renderer, _map1, nullptr, &_gcrR);

    _gcrR = {(g_weight / 4) + 180 + HEIGHT_SCOREBOARD, g_height / 3, 180, 134};
    SDL_RenderCopy(renderer, _map2, nullptr, &_gcrR);

    SDL_Rect r;
    if (n == 1) {
        r = {(g_weight / 4)  - 10, (g_height / 3) - 10, 200, 150};
    } else if (n == 2) {
        r = {(g_weight / 4) + (90 * 2) + HEIGHT_SCOREBOARD - 10, (g_height / 3) - 10, 200, 150};
    }

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &r);
}

void SDL_lib::cleanWindow() {
    SDL_DestroyTexture(_textureMap);
    SDL_DestroyTexture(_map1);
    SDL_DestroyTexture(_map2);
    SDL_DestroyTexture(_textureFood);
    SDL_DestroyTexture(_textureBigFood);
    SDL_DestroyTexture(_textureArrow);
    SDL_DestroyTexture(_textureLine);
    SDL_DestroyTexture(_textureText);
    SDL_DestroyTexture(_textureScore);
    SDL_DestroyTexture(_textureGameOver);
    for(auto&& it : _snakeTexture){
        SDL_DestroyTexture(it.second);
    }

    for(auto&& it : _buttonTexture){
        SDL_DestroyTexture(it.second);
    }
    TTF_CloseFont(_font);
    TTF_CloseFont(_game_over);
    _font = nullptr;
    _game_over = nullptr;

    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

extern "C"  AView* getInstance(int weight, int height) {
    return new SDL_lib(weight, height);
}

extern "C" void		destroy_object(SDL_lib *gui)
{
    printf("delete\n");
    delete gui;
}