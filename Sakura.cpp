#include "Sakura.h"
Sakura::Sakura(const char *texturesheet): Map_object(texturesheet){
    dest.w = SAKURA_SIZE_W;
    dest.h = SAKURA_SIZE_H;
    type = Type::sakura;
}

void Sakura::Draw() {
    TextureManager::Draw(object, dest);
}

