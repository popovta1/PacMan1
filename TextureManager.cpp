
#include "TextureManager.h"
#include <iostream>

/**
 * method to load texture from file
 * @param texture
 * @return
 */
SDL_Texture *TextureManager::LoadTexture(const char *texture) {
    SDL_Surface * tempSurface = IMG_Load(texture);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

/**
 * method to draw texture
 * @param tex
 * @param dest
 */
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect dest) {
    SDL_RenderCopy(Game::renderer,tex, NULL, &dest);
}


/**
 * method to print text
 * @param s
 */
void TextureManager::PrintText(string const & s,int startx, int starty, int texW, int texH, int size) {
    TTF_Font *x = TTF_OpenFont("./src/Arial.ttf", size);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *text = TTF_RenderText_Solid(x, s.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, text);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {startx, starty, texW, texH};
    SDL_RenderCopy(Game::renderer, texture, NULL, &dstrect);
    TTF_CloseFont(x);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text);
}