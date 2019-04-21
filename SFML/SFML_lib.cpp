//
// Created by Таня on 15.01.2019.
//

#include "SFML_lib.hpp"
#include <unistd.h>

const char tail_path[] = "/Picture/snake_tails.png";
const char body_path[] = "/Picture/snake_body.png";
const char head_path[] = "/Picture/snake_head.png";
const char map_1[] = "/Picture/map_1.png";
const char map_2[] = "/Picture/map_2.png";
const char lilFood[] = "/Picture/f.png";
const char bigFood[] = "/Picture/bigfood.png";
const char buttonSingle_path[] = "/Picture/button1.png";
const char buttonMulti_path[] = "/Picture/button2.png";
extern const char buttonOption_path[] = "/Picture/options.png";
extern const char buttonContinue_path[] = "/Picture/continue.png";
extern const char buttonExit_path[] = "/Picture/exit.png";
const char arrow_path[] = "/Picture/arrow_path.png";
const char gameOver_path[] = "/Picture/gameOver.png";
const char font_path[] = "/Picture/ArialItalic.ttf";

sf::RenderWindow* SFML_lib::_window = nullptr;

SFML_lib::SFML_lib() {
    std::cout << "CLOSE LIB SFML" << std::endl;
}

SFML_lib::SFML_lib(int g_weight, int g_height) {
    weight = g_weight;
    height = g_height;
    height_scoreboard = g_weight / 14;
    sizeFont = height_scoreboard / 4;

}

SFML_lib::~SFML_lib() {

}

void SFML_lib::init() {
    _window = new sf::RenderWindow(sf::VideoMode(weight, height + height_scoreboard, 32), "Nibbler");
    char path[4096];
    _dir = getwd(path);
    _textureMap1.loadFromFile((_dir + map_1).c_str());
    _textureMap2.loadFromFile((_dir + map_2).c_str());
    _snakeTexture[0].loadFromFile((_dir + tail_path).c_str());
    _snakeTexture[1].loadFromFile((_dir + body_path).c_str());
    _snakeTexture[2].loadFromFile((_dir + head_path).c_str());
    _textureFood.loadFromFile((_dir + lilFood).c_str());
    _textureBigFood.loadFromFile((_dir + bigFood).c_str());
    _textureArrow.loadFromFile((_dir + arrow_path).c_str());
    arrow.setTexture(_textureArrow);
    _buttonTexture["single"].loadFromFile((_dir + buttonSingle_path).c_str());
    _buttonTexture["multi"].loadFromFile((_dir + buttonMulti_path).c_str());
    _buttonTexture["option"].loadFromFile((_dir + buttonOption_path).c_str());
    _buttonTexture["continue"].loadFromFile((_dir + buttonContinue_path).c_str());
    _buttonTexture["exit"].loadFromFile((_dir + buttonExit_path).c_str());
    _gameOver.loadFromFile((_dir + gameOver_path).c_str());
    GameOver.setTexture(_gameOver);
    font.loadFromFile((_dir + font_path).c_str());
    text.setFont(font);
    text.setCharacterSize(sizeFont);
    text.setFillColor(sf::Color::Red);
    over.setFont(font);
    over.setCharacterSize(height_scoreboard / 3);
    over.setFillColor(sf::Color::Green);
    timeBigFood.loadFromFile((_dir + map_1).c_str(), sf::IntRect(10, 10, 5, sizeFont - 10));

}

void SFML_lib::initMap(int n) {
    if (n == 1){
        map.setTexture(_textureMap1);
    }
    else if(n == 2) {
        map.setTexture(_textureMap2);
    }
}

int SFML_lib::catchHook(){
    while(_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            return -1;
        }
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Escape:
                    return ' ';
                case sf::Keyboard::W:
                    return 'w';
                case sf::Keyboard::S:
                    return 's';
                case sf::Keyboard::D:
                    return 'd';
                case sf::Keyboard::A:
                    return 'a';
                case sf::Keyboard::Space:
                    return ' ';
                case sf::Keyboard::Up:
                    return 126;
                case sf::Keyboard::Down:
                    return 125;
                case sf::Keyboard::Left:
                    return 123;
                case sf::Keyboard::Right:
                    return 124;
                case sf::Keyboard::Return:
                    return 36;
                case sf::Keyboard::Num1:
                    return 1;
                case sf::Keyboard::Num2:
                    return 2;
                case sf::Keyboard::Num3:
                    return 3;
                default:
                    return 0;
            }
        }
    }
    return 0;
}

uint32_t SFML_lib::getTicks() {
    sf::Time time = _clock.getElapsedTime();
    return static_cast<uint32_t>(time.asMilliseconds());
}

void SFML_lib::delay(int time) {
    sf:: sleep(sf::milliseconds(time));
}

void SFML_lib::render() {
    _window->display();

}

void SFML_lib::drawMenu(void* rectA, void* rectB, int typeMenu) {
    _window->pollEvent(_event);
    _window->clear();
    t_scr A = *reinterpret_cast<t_scr*>(rectA);
    t_scr B = *reinterpret_cast<t_scr*>(rectB);
    arrow.setPosition(A.x, A.y);
    auto size = arrow.getTexture()->getSize();
    arrow.setScale(float(A.w)/size.x, float(A.h)/size.y);
    _window->draw(arrow);
    if (typeMenu == 3) {
        button.setTexture(_buttonTexture["continue"]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w) / size.x, float(B.h) / size.y);
        button.setPosition(B.x, B.y);
        _window->draw(button);
        button.setTexture(_buttonTexture["option"]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w) / size.x, float(B.h) / size.y);
        B.y += B.h + 10;
        button.setPosition(B.x, B.y);
        _window->draw(button);
        button.setTexture(_buttonTexture["exit"]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w) / size.x, float(B.h) / size.y);
        B.y += B.h + 10;
        button.setPosition(B.x, B.y);
        _window->draw(button);
    }
    else {
        button.setTexture(_buttonTexture["single"]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w)/size.x, float(B.h)/size.y);
        button.setPosition(B.x, B.y);
        _window->draw(button);
        button.setTexture(_buttonTexture["multi"]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w)/size.x, float(B.h)/size.y);
        B.y += B.h + 10;
        button.setPosition(B.x, B.y);
        _window->draw(button);
        button.setTexture(_buttonTexture["option"]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w)/size.x, float(B.h)/size.y);
        B.y += B.h + 10;
        button.setPosition(B.x, B.y);
        _window->draw(button);
        button.setTexture(_buttonTexture["exit"]);
        size = button.getTexture()->getSize();
        button.setScale(float(B.w)/size.x, float(B.h)/size.y);
        B.y += B.h + 10;
        button.setPosition(B.x, B.y);
        _window->draw(button);
    }
}



void SFML_lib::drawMap() {
    _window->pollEvent(_event);
    _window->clear();
    map.setPosition(0, height_scoreboard);
    auto size = map.getTexture()->getSize();
    map.setScale(float(weight)/size.x, float(height)/size.y);
    _window->draw(map);
}

void SFML_lib::drawSnake(void* rect, int b_block) {//b_block - wich texture render: tail, body, head
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    snake.setTexture(_snakeTexture[b_block]);
    auto size = snake.getTexture()->getSize();
    snake.setScale(float(_fcrR.w)/size.x, float(_fcrR.h)/size.y);
    snake.setPosition(_fcrR.x, _fcrR.y);
    _window->draw(snake);
 }

void SFML_lib::drawFood(void* rect) {
    sf::Sprite food;
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    food.setTexture(_textureFood);
    auto size = food.getTexture()->getSize();
    food.setScale(float(_fcrR.w)/size.x, float(_fcrR.h)/size.y);
    food.setPosition(_fcrR.x, _fcrR.y);
    _window->draw(food);
}

void SFML_lib::drawBigFood(void* rect) {
    sf::Sprite food;
    t_scr _fcrR = *reinterpret_cast<t_scr*>(rect);
    food.setTexture(_textureBigFood);
    auto size = food.getTexture()->getSize();
    food.setScale(float(_fcrR.w)/size.x, float(_fcrR.h)/size.y);
    food.setPosition(_fcrR.x, _fcrR.y);
    _window->draw(food);
}

void SFML_lib::drawInterface(std::string clock, int score) {

    text.setString(clock);
    text.setPosition(50, height_scoreboard / 2);
    _window->draw(text);
    text.setString("Score:   " + std::to_string(score));
    text.setPosition(weight / 3, height_scoreboard / 2);
    _window->draw(text);
}

void SFML_lib::drawTimeBigFood(int time) {
    sf::Sprite sprite;
    sprite.setTexture(timeBigFood);
    sprite.setColor(sf::Color::Green);
    for (int i = 0; i < time; i++) {
        sprite.setPosition((weight / 3) * 2 + (3 * i), height_scoreboard / 2);
        _window->draw(sprite);
    }
}

void SFML_lib::drawChangeMap(int n) {
     _window->pollEvent(_event);
    _window->clear();
    _map = &_textureMap1;
    auto size = _textureMap1.getSize();
    sf::RectangleShape t1(sf::Vector2f(360, 268));
    t1.setTexture(_map);
    t1.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    t1.setPosition(weight / 4, height / 3);

    _map = &_textureMap2;
    size = _textureMap2.getSize();
    sf::RectangleShape t2(sf::Vector2f(360, 268));
    t2.setTexture(_map);
    t2.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    t2.setPosition((weight / 4) + (90 * 4) +height_scoreboard, height / 3);
    if (n == 1) {
        t1.setOutlineThickness(10.f);
        t1.setOutlineColor(sf::Color(250, 150, 100));
    }
    else if( n == 2) {
        t2.setOutlineThickness(10.f);
        t2.setOutlineColor(sf::Color(250, 150, 100));
    }
    _window->draw(t1);
    _window->draw(t2);


}

void SFML_lib::renderClear() {

}

void SFML_lib::cleanWindow() {
    _window->clear();
    _window->close();
    delete _window;
}

void SFML_lib::drawGameOver(int score) {
    _window->pollEvent(_event);
    _window->clear();
    auto size = GameOver.getTexture()->getSize();
    GameOver.setScale((weight/3)/size.x, (height/3)/size.y);
    GameOver.setPosition((weight / 3) , (height / 3));
    _window->draw(GameOver);
    over.setString("SCORE:    " + std::to_string(score));
    over.setPosition( (weight / 2) - height_scoreboard , (height / 3) * 2);
    _window->draw(over);
    over.setString("Please, press space key");
    over.setPosition((weight / 2 - height_scoreboard * 2), (height - height_scoreboard));
    _window->draw(over);
}

extern "C"  AView* getInstance(int weight, int height) {
    return new SFML_lib(weight, height);
}

extern "C" void		destroy_object(SFML_lib *gui) {
    delete gui;
}
