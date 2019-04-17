#include <regex>
#include "Game_Obj.hpp"
#include "global.h"


int g_weight;
int g_height;
int g_lib;
int HEIGHT_SCOREBOARD;
bool _mapInit;


int size(int n, int g){
    if (g == 1) {
        if (n % 90 == 0)
            return n;
        else
            return (90 *(n / 90));
    }
    else if (g == 2) {
        return (67 * (g_weight / 90));
    }
    return 0;
}

int main(int argc, char **argv){

    std::regex check("[\\s]*?\\d{3,4}[\\s]*?$");
    try {
        if (argc != 4) {
            throw std::logic_error("usage: [width] [height] [1|2|3]");
        }
        for (int i = 1; i < argc; ++i) {
            if (!std::regex_match(*(argv + i), (i != 3) ? check : std::regex("[\\s]*?\\d{1}[\\s]*?$"))) {
                throw std::logic_error("usage: [width] [height] [1|2|3]");
            }
            if (i == 1) {
                g_weight = size(std::stoi(*(argv + i)), 1);
                if (g_weight > 1620 || g_weight < 720) {
                    throw std::logic_error("width >= 720 && width <= 1620");
                }
            } else if (i == 2) {
                g_height = size(std::stoi(*(argv + i)), 2);
                if (g_height > 1206 || g_height < 536) {
                    throw std::logic_error("height >= 536 && height <= 1206");
                }
            } else if (i == 3) {
                g_lib = std::stoi(*(argv + i));;
                if (g_lib > 3) {
                    throw std::logic_error("usage: [width] [height] [1|2|3]");
                }
            }
        }
    }catch (std::exception& e){
        std::cout << e.what() << std::endl;
        exit(1);
    }

    if (g_lib == 2){
        g_weight *= 2;
        g_height *= 2;
    }

    HEIGHT_SCOREBOARD = g_weight / 14;
    _mapInit = false;
    try {
        std::shared_ptr<Game_Obj> obj(new Game_Obj);
        obj->init();
    }catch(...){
        std::cout << "Something wrong :)" << std::endl;
    }
    return 0;
}