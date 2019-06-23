#include "Map_object.h"
#include "TextureManager.h"


//constructor of virtial class loads texture
Map_object::Map_object(const char *texture) {
    object = TextureManager::LoadTexture(texture);
}

//destructor destroy texture
Map_object::~Map_object() {
    Delete();
}

void Map_object::Delete() { 
    SDL_DestroyTexture(object);
}

// set position for map object
void Map_object::SetDest(int x, int y) {
    dest.x = x;
    dest.y = y;
}

//getter for type of map object
Type Map_object::GetType() const {
    return type;
}

