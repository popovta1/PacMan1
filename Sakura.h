#include "Map_object.h"
#include "game.h"
#include "defs.h"
#ifndef PAC_MAN_SAKURA_H
#define PAC_MAN_SAKURA_H
class Sakura : public Map_object {
public:
    Sakura(const char* texturesheet);
    void Draw();
};
#endif //PAC_MAN_SAKURA_H
