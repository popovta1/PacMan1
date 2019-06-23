#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "game.h"
#include <SDL2/SDL_ttf.h>
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
class TextureManager {
public:
    static SDL_Texture * LoadTexture (const char * texture);
    ~TextureManager();
    static void Draw(SDL_Texture* tex, SDL_Rect dest);
    static void PrintText(string const & s,int startx, int starty, int texW, int texH, int size);

};

#endif //TEXTURE_MANAGER_H