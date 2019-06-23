#ifndef GAME_H
#define GAME_H

#include "RedSamurai.h"
#include "YellowSamurai.h"
#include "GreenSamurai.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ninja.h"
#include "Map.h"
#include <iostream>
#include "GameObject.h"


class Game {
public:
    Game();

    ~Game();

    void Move();

    void Init(const char *title, int xpos, int ypos, int weight, int heiht, bool fullscreen);

    void HandleEvent();

    void HandleInput();

    void Update();

    void Render();

    void Clean();

    void HandlePoints();

    void InitObjects();

    bool Running();

    static SDL_Renderer *renderer;

private:
    shared_ptr<Ninja> ninja;
    shared_ptr<RedSamurai> redSamurai;
    shared_ptr<GreenSamurai> greenSamurai;
    shared_ptr<YellowSamurai> yellowSamurai;
    shared_ptr<Map> map;
    bool isRunning;
    int timerForChaseMode;
    int timerForFrightenedMode;
    int timerForScatterMode;
    SDL_Window *window;
    void ChangeModeScatter();
    void ChangeModeChase();
    void ChangeModeFrightened();

};

#endif //GAME_H