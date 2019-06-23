
#include "TextureManager.h"
#include "GameObject.h"
#include <utility>
#include "defs.h"
#ifndef NINJA_H
#define NINJA_H
using namespace std;


class Ninja :public GameObject {
public:
    explicit Ninja(const char *texturesheet);
    int GetScore() const;
    void AddScore(int price);
    int GetXPos() const;
    int GetYPos() const;
    void PrintScores() const;
    void Restart();
    int GetSpeed() const;
    int GetCurScore() const;
    void SetStartPos(shared_ptr<Map> map);
    bool IsCollisionSamuraiRoom() const;

private:
    int score;
};

#endif //NINJA_H