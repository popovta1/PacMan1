#include "Grass.h"

/**
 * constructor sets parameters for grass type of map object
 * @param texturesheet
 */
Grass::Grass(const char *texturesheet) : Map_object(texturesheet) {
    src.x = 0;
    src.y = 0;
    src.w = GRASS_IMAGE_SIZE_W;
    src.h = GRASS_IMAGE_SIZE_H;
    dest.w = GRASS_SIZE_W;
    dest.h = GRASS_SIZE_H;
    type = Type::grass;
}

//draw grass
void Grass::Draw() {
    SDL_RenderCopy(Game::renderer,object, &src, &dest);
}


