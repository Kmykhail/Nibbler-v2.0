//
// Created by kmykhailenko on 14.03.19.
//

#ifndef GLFW_GAMEWINDOW_HPP
#define GLFW_GAMEWINDOW_HPP

#include <GL/glew.h>
#include <freetype2/ft2build.h>
#include <FTGL/ftgl.h>
#include <GLFW/glfw3.h>
#include "../AView.hpp"
#ifdef __APPLE__
    #include <GLUT/glut.h>
#endif

#ifdef __linux__
    #include <GL/glut.h>
#endif

#include <iostream>
#include <SOIL.h>
#include <fstream>
#include <string>
#include <map>
#include <unistd.h>


typedef struct s_glScr{
    int x;
    int y;
    int w;
    int h;
}               t_glScr;

class GL_lib : public AView{
private:
    GLFWwindow*     _window;
    std::string     _dir;
    int             g_weight;
    int             g_height;
    int             HEIGHT_SCOREBOARD;
    int             SizeFont;


    GLuint          _textureMap;
    GLuint          _map1;
    GLuint          _map2;
    GLuint          _textureFood;
    GLuint          _textureBigFood;
    GLuint          _textureArrow;
    GLuint          _textureLine;
    GLuint          _textureGameOver;
    GLuint          _textureScore;
    std::map<std::string, GLuint>   _textureButton;
    std::map<int, GLuint > _textureSnake;

    t_glScr           _scrR;//snake
    t_glScr           _fcrR;//food
    t_glScr           _lcrR;//line time
    t_glScr           _mcrR;//menu
    t_glScr           _gcrR;//target map
    int               _size_block;
    FTGLPixmapFont*   _font;

    void LoadImage();
    void DrawEveryThing(t_glScr glScr, GLuint& drawThis);
public:
    GL_lib();
    GL_lib(int weight, int height);
    ~GL_lib();
    void    init() override;
    void    initMap(int) override;
    int     catchHook() override;
    void    render() override;
    void    drawMenu(void*, void*, int) override;
    void    drawMap() override;
    void    drawSnake(void*, int) override;
    void    renderClear() override;
    uint32_t getTicks() override;
    void    delay(int) override;
    void    cleanWindow() override;
    void    drawFood(void* rect) override;
    void    drawBigFood(void*) override;
    void    drawInterface(std::string clock, int score) override;
    void    drawTimeBigFood(int time) override;
    void    drawGameOver(int) override;
    void    drawChangeMap(int)   override;

    static int  _buttonStatus;
};

#endif