#include "Map_object.h"


class Pancake:public Map_object {
public:
    explicit Pancake(const char *texturesheet);
    void Draw();

};

