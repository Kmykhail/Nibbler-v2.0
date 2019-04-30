//
// Created by kmykhailenko on 23.01.19.
//

/*******************ONLY FOR SDL************************/
#include "TextureManager.hpp"

TextureManager::TextureManager() {}
TextureManager::~TextureManager() {}

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

SDL_Texture* TextureManager::LoadTexture(const char *filename) {
    SDL_Surface *tmp_surface = IMG_Load(filename);
    if (!tmp_surface){
        std::cerr << "Error tmp_surface" << std::endl;
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(SDL_lib::renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
    return  texture;
}
SDL_Texture* TextureManager::LoadTextureText(const char *filename, SDL_Color& color, SDL_Rect& tcrR) {
    SDL_Surface *tmp_surface = TTF_RenderText_Solid(SDL_lib::_font, filename, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(SDL_lib::renderer, tmp_surface);
    tcrR.w = tmp_surface->w;
    tcrR.h = tmp_surface->h;
    SDL_FreeSurface(tmp_surface);
    return texture;
}
/*******************ONLY FOR SDL************************/
