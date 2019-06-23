
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_ttf.h>
#include "Ninja.h"

/**constructor for ninja class
 * set size of ninja object and its speed
 * @param texturesheet
 */
Ninja::Ninja(const char *texturesheet) : GameObject(texturesheet), score(0) {
    destRec.w = NINJA_SIZE_W;
    destRec.h = NINJA_SIZE_H;
    speed = NINJA_SPEED;

}
//get current point number
int Ninja::GetScore() const {
    return score;
}

/**
 * set ninja to the start position
 */
void Ninja::Restart() {
        xpos = StartPos.first;
        ypos = StartPos.second;
}

/**
 * Get different parameters of the ninja class
 * @return
 */
int Ninja::GetXPos() const {
    return xpos;
}

int Ninja::GetYPos() const {
    return ypos;
}

int Ninja::GetSpeed() const {
    return speed;
}


void Ninja::AddScore(int price) {
    score += price;
}

int Ninja::GetCurScore() const {
    return score;
}

//print current point number
void Ninja::PrintScores() const {
    string s = "Score: ";
    s += to_string(score);
   TextureManager::PrintText(s, 0, 0, 0, 0, 25);

}

void Ninja::SetStartPos(shared_ptr<Map> map) {
    StartPos = map->GetNinjaPos();
}
