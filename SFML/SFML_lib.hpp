//
// Created by Таня on 15.01.2019.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "AView.hpp"
#include "Mmap.hpp"
#include "header.h"
#include "global.h"
#include <map>


class SFML_lib: public AView{
public:
    explicit SFML_lib(int g_weight, int g_height);
    ~SFML_lib();

    void    init() override;
    void    initMap(int) override;
    void    render() override;
    void    drawMap() override;
    void    drawMenu(void*, void*, int) override;
    void    drawSnake(void*, int) override;
    void    delay(int) override;
    void    cleanWindow() override;
    void    drawFood(void*) override;
    void    drawBigFood(void*) override;
    void    drawInterface(std::string, int) override;
    void    drawTimeBigFood(int) override;
    void    renderClear() override;
    void    drawGameOver(int) override;
    void    drawChangeMap(int)   override;
    int     catchHook() override;
    uint32_t getTicks() override;

private:
    static sf::RenderWindow *_window;
    sf::Event   _event;
    sf::Clock   _clock;
    sf::Texture _textureMap1;
    sf::Texture _textureMap2;
    sf::Texture _textureFood;
    sf::Texture _textureBigFood;
    sf::Texture _textureArrow;
    sf::Texture timeBigFood;
    sf::Texture _gameOver;
    sf::Sprite  GameOver;
    sf::Sprite  map;
    sf::Sprite  arrow;
    sf::Sprite  button;
    sf::Sprite snake;
    std::map<int, sf::Texture> _snakeTexture;
    std::map<std::string, sf::Texture> _buttonTexture;
    sf::Font font;
    sf::Text text;
    sf::Text over;
    const sf::Texture *_map;
    int weight;
    int height;
    int height_scoreboard;
    int sizeFont;
    std::string _dir;
    SFML_lib(const SFML_lib&) = delete;
    SFML_lib& operator=(const SFML_lib&) = delete;

    SFML_lib(SFML_lib&&) = delete;
    SFML_lib& operator=(SFML_lib&&) = delete;
};

