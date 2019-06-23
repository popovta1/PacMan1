#include "SDL2/SDL.h"
#include "defs.h"
#ifndef PAC_MAN_MAP_OBJECT_H
#define PAC_MAN_MAP_OBJECT_H
class Map_object {
public:
    Map_object(const char * texture);
    ~Map_object();
    virtual void Draw() = 0;
    void SetDest (int x, int y);
    void Delete();
    Type GetType() const;

protected:
    Type type;
    SDL_Texture * object;
    SDL_Rect src, dest;
};
#endif //PAC_MAN_MAP_OBJECT_H
