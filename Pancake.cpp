#include "Pancake.h"
#include "defs.h"
#include "game.h"

Pancake::Pancake(const char *texturesheet) : Map_object(texturesheet) {
    src.x = 0;
    src.y = 0;
    src.w = PANCAKE_IMAGE_SIZE_W;
    src.h = PANCAKE_IMAGE_SIZE_H;
    dest.w = PANCAKE_SIZE_W;
    dest.h = PANCAKE_SIZE_H;
    type = Type::pancake;
}

void Pancake::Draw() {
    TextureManager::Draw(object, dest);
}