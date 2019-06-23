#include <utility>
#include "Map_object.h"
#include "vector"
#include <memory>
#include "SDL2/SDL.h"
#include "defs.h"
#include <utility>
#include "Map.h"
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
using namespace std;

class GameObject {
public:
    explicit GameObject(const char *texturesheet);

    ~GameObject();

    void SetDirection(Dir newDir);

    void SetPos(std::pair<int, int> newPos);

    void Update();

    bool IsPossible(shared_ptr<Map> map);

    bool CollisionSamuraiRoom(shared_ptr<Map>  map);

    Dir GetDir() const;

    void LeftDir();

    void RightDir();

    void ForwardMove();

    void BackwardMove();

    void Move(Dir dir);

    void Move();

    void Teleport();

    pair<int, int> GetDownLeftCorner() const;

    pair<int, int> GetDownRightCorner() const;

    pair<int, int> GetUpLeftCorner() const;

    pair<int, int> GetUpRightCorner() const;

    pair<int, int> GetCenter() const;

    void SetSpeed(int newSpeed);

    virtual void Restart() = 0;

    virtual void SetStartPos(shared_ptr<Map> map) = 0;

    void Render();

protected:
    int xpos;
    int ypos;
    int speed;
    pair<int, int> StartPos;
    Dir curDir;
    SDL_Texture *objTexture;
    SDL_Rect destRec;

};

#endif //GAME_OBJECT_H