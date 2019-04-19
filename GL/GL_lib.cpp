//
// Created by kmykhailenko on 14.03.19.
//

#include "GL_lib.hpp"
#include <thread>
#include <string.h>
#include <string>

#define CREATE_TEXTURE(str) SOIL_load_OGL_texture(str, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT)

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
const char font_path[] = "/Picture/ArialItalic.ttf";
const char gameOver_path[] = "/Picture/gameOver.png";

int GL_lib::_buttonStatus = 0;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS){
        switch (key){
            case GLFW_KEY_ESCAPE:
                std::cout << "PAUSE" << std::endl;
                GL_lib::_buttonStatus = ' ';
                return;
            case GLFW_KEY_W:
                std::cout << "w" << std::endl;
                GL_lib::_buttonStatus = 'w';
                return;
            case GLFW_KEY_S:
                std::cout << "s" << std::endl;
                GL_lib::_buttonStatus= 's';
                return;
            case GLFW_KEY_D:
                std::cout << "d" << std::endl;
                GL_lib::_buttonStatus= 'd';
                return;
            case GLFW_KEY_A:
                std::cout << "a" << std::endl;
                GL_lib::_buttonStatus= 'a';
                return;
            case GLFW_KEY_SPACE:
                std::cout << "space" << std::endl;
                GL_lib::_buttonStatus= ' ';
                return;
            case GLFW_KEY_UP:
                GL_lib::_buttonStatus= 126;
                return;
            case GLFW_KEY_DOWN:
                GL_lib::_buttonStatus= 125;
                return;
            case GLFW_KEY_LEFT:
                GL_lib::_buttonStatus = 123;
                return;
            case GLFW_KEY_RIGHT:
                GL_lib::_buttonStatus = 124;
                return;
            case GLFW_KEY_ENTER:
                GL_lib::_buttonStatus = 36;
                return;//enter
            case GLFW_KEY_1://change current lib on SDL
                GL_lib::_buttonStatus = 1;
                return;
            case GLFW_KEY_2://change current lib on SFML
                GL_lib::_buttonStatus = 2;
                return;
            case GLFW_KEY_3://change current lib on ALLEGRO
                GL_lib::_buttonStatus = 3;
                return;
            default:
                GL_lib::_buttonStatus = 0;
                return;
        }
    }
}

GL_lib::GL_lib() {}

GL_lib::GL_lib(int weight, int height) {
    g_weight = weight;
    g_height = height;
    HEIGHT_SCOREBOARD = g_weight / 14;
    SizeFont = HEIGHT_SCOREBOARD / 4;
    _size_block = (g_weight / 90);
}

GL_lib::~GL_lib() {}

void GL_lib::init()
{
    if (!glfwInit()){
        std::cerr << "Error Init" << std::endl;
        exit(1);
    }

    if (!(_window = glfwCreateWindow(g_weight, g_height + HEIGHT_SCOREBOARD, "Snake", nullptr, nullptr))){
        std::cerr <<  "Error Create Window" << std::endl;
        exit(1);
    }

    glfwSetKeyCallback(_window, keyCallback);
    glfwMakeContextCurrent(_window);

    if (!glfwGetCurrentContext()){
        std::cerr << "Couldn't create OpenGL context" << std::endl;
        exit(1);
    }

    GLenum err = glewInit();
    if (GLEW_OK != err){
        std::cerr << glewGetErrorString(err) <<std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    char path[4096];
    _dir = getwd(path);

    /*****************INIT FONT*****************/

    _font = nullptr;
    if (!(_font = new FTGLPixmapFont((_dir + font_path).c_str()))){
        std::cerr << "Trouble load font" << std::endl;
        exit(1);
    }

    _font->FaceSize(SizeFont * 2);
    LoadImage();
}

void GL_lib::LoadImage()
{
    /*************LOAD MAP TEXTURE*************/
    if (!(_map1 = CREATE_TEXTURE((_dir + map_1).c_str()))) {
        std::cerr << "Not load texture map" << std::endl;
        exit(1);
    }
    if (!(_map2 = CREATE_TEXTURE((_dir + map_2).c_str()))) {
        std::cerr << "Not load texture map" << std::endl;
        exit(1);
    }
    /*************LOAD SNAKE TEXTURE*************/
    _textureSnake = {
                        {0, CREATE_TEXTURE((_dir + tail_path).c_str())},
                        {1, CREATE_TEXTURE((_dir + body_path).c_str())},
                        {2, CREATE_TEXTURE((_dir + head_path).c_str())}
                    };
    if (_textureSnake.empty()){
        std::cerr << "Not load texture snake" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR FOOD************/
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
    /************INIT TEXTURE FOR BUTTON***********/
    _textureButton = {{"single", CREATE_TEXTURE((_dir + buttonSingle_path).c_str())}, {"multi", CREATE_TEXTURE((_dir + buttonMulti_path).c_str())},
                      {"continue", CREATE_TEXTURE((_dir + buttonContinue_path).c_str())}, {"option", CREATE_TEXTURE((_dir + buttonOption_path).c_str())},
                      {"exit", CREATE_TEXTURE((_dir + buttonExit_path).c_str())}};
    if (_textureButton.empty()){
        std::cerr << "textureButton not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR ARROW************/
    _textureArrow = CREATE_TEXTURE((_dir + arrow_path).c_str());
    if (!_textureArrow){
        std::cerr << "textureArrow not exist" << std::endl;
        exit(1);
    }
    /************INIT TEXTURE GAME OVER************/
    _textureGameOver = CREATE_TEXTURE((_dir + gameOver_path).c_str());
    if (!_textureGameOver){
        std::cerr << "textureGameOver not exist" << std::endl;
        exit(1);
    }
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    std::cout << "LOAD DONE" << std::endl;
}

void GL_lib::DrawEveryThing(t_glScr glScr, GLuint &drawThis) {
    glfwMakeContextCurrent(_window);
    glViewport(glScr.x * 2, glScr.y * 2, glScr.w * 2, glScr.h * 2);

    glClearColor(0.f, 0.f, 0.f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (drawThis != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, drawThis);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    glBegin(GL_QUADS);

    glTexCoord2f(0.f, 0.f);
    glVertex2f(-1.f, -1.f);

    glTexCoord2f(1.f, 0.f);
    glVertex2f(1.f, -1.f);

    glTexCoord2f(1.f, 1.f);
    glVertex2f(1.f, 1.f);

    glTexCoord2f(0.f, 1.f);
    glVertex2f(-1.f, 1.f);

    glEnd();
}


void GL_lib::drawMap() {
    t_glScr tmp = {0, 0, g_weight, g_height};
    DrawEveryThing(tmp, _textureMap);
}

void GL_lib::initMap(int n) {
    if (n == 1){
        if (!(_textureMap = CREATE_TEXTURE((_dir + map_1).c_str()))){
            std::cerr << "textuteMap1 not exist" << std::endl;
            exit(1);
        }
    }
    else if (n == 2){
        if (!(_textureMap = CREATE_TEXTURE((_dir + map_2).c_str()))){
            std::cerr << "textuteMap2 not exist" << std::endl;
            exit(1);
        }
    }
}

int GL_lib::catchHook() {
    glfwPollEvents();
    int sym = _buttonStatus;
    _buttonStatus = 0;
    return sym;
}

uint32_t GL_lib::getTicks() {
    return glfwGetTime();
}

void GL_lib::delay(int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void GL_lib::render()
{
    glfwSwapBuffers(_window);
}

void GL_lib::drawMenu(void* rectA, void* rectB, int typeMenu) {
    if (!rectA || !rectB) {
        std::cerr << "Trouble with rectA or rectB" << std::endl;
        exit(1);
    }
    _mcrR = *reinterpret_cast<t_glScr*>(rectA);
    _mcrR.y =  g_height - _mcrR.y;
    DrawEveryThing(_mcrR, _textureArrow);
    _mcrR = *reinterpret_cast<t_glScr*>(rectB);
    _mcrR.y =  g_height - _mcrR.y;
    if (typeMenu == 3){
        DrawEveryThing(_mcrR, _textureButton["continue"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["option"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["exit"]);
    }
    else{
        DrawEveryThing(_mcrR, _textureButton["single"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["multi"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["option"]);
        _mcrR.y += (_mcrR.h + 10) * -1;
        DrawEveryThing(_mcrR, _textureButton["exit"]);
    }
}

void GL_lib::drawSnake(void* rect, int b_block) {
    if (!rect){
        std::cout << "Rect is NULL" << std::endl;
        exit(1);
    }

    _scrR = *reinterpret_cast<t_glScr*>(rect);
    _scrR.y = (g_height + HEIGHT_SCOREBOARD) - _scrR.y - _size_block;
    DrawEveryThing(_scrR, _textureSnake[b_block]);
}

void GL_lib::drawFood(void *rect) {
    if (!rect){
        std::cout << "Rect is NULL" << std::endl;
        exit(1);
    }

    _fcrR = *reinterpret_cast<t_glScr*>(rect);
    _fcrR.y = (g_height + HEIGHT_SCOREBOARD) - _fcrR.y - _size_block;
    DrawEveryThing(_fcrR, _textureFood);
}

void    GL_lib::drawBigFood(void *rect) {
    _fcrR = *reinterpret_cast<t_glScr*>(rect);
    _fcrR.y = (g_height + HEIGHT_SCOREBOARD) - _fcrR.y - (_size_block * 2);
    DrawEveryThing(_fcrR, _textureBigFood);
}

void GL_lib::drawInterface(std::string clock, int score){
    std::string scoreStr = "Score:   " + std::to_string(score);
    _font->Render(clock.c_str(), clock.length(), FTPoint(100, (g_height + HEIGHT_SCOREBOARD  - (HEIGHT_SCOREBOARD / 2))* 2));
    _font->Render(scoreStr.c_str(), scoreStr.length(), FTPoint((g_weight / 3) * 2, (g_height + HEIGHT_SCOREBOARD  - (HEIGHT_SCOREBOARD / 2))* 2) );
}

void GL_lib::drawTimeBigFood(int time) {
    _lcrR = {(g_weight / 3) * 2, (g_height + HEIGHT_SCOREBOARD / 2), time, SizeFont - 10};
    DrawEveryThing(_lcrR, _textureLine);
}

void GL_lib::renderClear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void GL_lib::drawGameOver(int score) {
    _gcrR = {(g_weight / 3), g_height / 3, g_weight / 3, g_height / 3};
    DrawEveryThing(_gcrR, _textureGameOver);
    std::string scoreStr = "Score:   " + std::to_string(score);
    _font->Render(scoreStr.c_str(), scoreStr.length(), FTPoint(((g_weight / 2) - HEIGHT_SCOREBOARD) * 2, (g_height / 3) * 2));
    _font->Render("Please, press space key", 23, FTPoint(((g_weight / 2) - HEIGHT_SCOREBOARD * 2) * 2, g_height - (g_height - HEIGHT_SCOREBOARD)));
}

void GL_lib::drawChangeMap(int n) {
    _gcrR = {g_weight / 4, g_height / 3, 180, 134};
    DrawEveryThing(_gcrR, _map1);
    _gcrR = {(g_weight / 4) + 180 + HEIGHT_SCOREBOARD, g_height / 3, 180, 134};
    DrawEveryThing(_gcrR, _map2);

    t_glScr square;
    if (n == 1){
        square = {(g_weight / 4)  - 10, (g_height / 3) - 10, 200, 150};
    }
    else if (n == 2) {
        square = {(g_weight / 4) + (90 * 2) + HEIGHT_SCOREBOARD - 10, (g_height / 3) - 10, 200, 150};
    }
    DrawEveryThing(square, (n == 1) ? _map1 : _map2);
}

void GL_lib::cleanWindow() {
    delete _font;
    glfwDestroyWindow(_window);
    glfwTerminate();
}

extern "C"  AView* getInstance(int weight, int height) {
    return new GL_lib(weight, height);
}

extern "C" void destroy_object(GL_lib *gui)
{
    printf("delete\n");
    delete gui;
}


