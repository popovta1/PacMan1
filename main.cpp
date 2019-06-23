#include "defs.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
Game * game = nullptr;
int main()
{
    const int FPC = 60;
    const int frameDelay = 1500 / FPC; // Непонятные константы в коде
    Uint32 frameStart;
    int frameTime;
    game = new Game();
    game->Init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WEIGHT, SCREEN_HEIGHT, false);
    /**
     * main game loop
     */
    while(game->Running()) {
        frameStart = SDL_GetTicks();
        game->HandleEvent();
        game->HandleInput();
        game->HandlePoints();
        game->Move();
        game->Update();
        game->Render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);

        }

    }
    game->Clean();
    return 0;
}
