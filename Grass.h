#include "Map_object.h"
#include "game.h"
#include "defs.h"


class Grass : public Map_object {
public:
    Grass(const char *texturesheet);
    void Draw();
private:


};

