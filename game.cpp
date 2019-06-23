#include <SDL2/SDL_ttf.h>
#include "game.h"
#include "defs.h"
#include "TextureManager.h"

SDL_Renderer *Game::renderer = nullptr;

using namespace std;

/**
 * default constructor
 */
Game::Game() {
    window = nullptr;
    renderer = nullptr;
}

Game::~Game() = default;

/**
 * initialize SDL renderer and create window
 */
void Game::Init(const char *title, int xpos, int ypos, int weight, int heiht, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        TTF_Init();
        //create window
        window = SDL_CreateWindow(title, xpos, ypos, weight, heiht, flags);
        //create render/ parameters: window, index, flags
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); //blue colour. colour of background
        } else {
            throw runtime_error("Window could not be created");
        }
        isRunning = true;
        InitObjects();
        timerForChaseMode = 0;
        timerForScatterMode = 0;
        timerForFrightenedMode = 0;
    }
    else {
        throw runtime_error("SDL could not initialize!");
    }

}

/**
 * collects point or bonus
 */
void Game::HandlePoints() {
    if (map->IfSakura(ninja->GetCenter())) {
        //delete found object from map
        map->RemovePoint(ninja->GetCenter().second, ninja->GetCenter().first);
        ninja->AddScore(1);
    }
    if (map->IfPancake(ninja->GetCenter())) {
        //delete found object from map
        map->RemovePoint(ninja->GetCenter().second, ninja->GetCenter().first);
        ninja->AddScore(10);
        ChangeModeFrightened();
    }
    if (ninja->GetCurScore() >= map->GetMaxScore()) {
        TextureManager::PrintText("You won!!!", 20, 20, 20, 20, 35); 
        isRunning = false;
    }
}

/**
 * handle input(key presses) to move ninja
 */
void Game::HandleInput() {
    vector<vector<shared_ptr<Map_object>>> curMap = map->GetMap();
    if (ninja->IsPossible(map) && !ninja->CollisionSamuraiRoom(map)) {
        ninja->Move();
    } else {
        ninja->SetDirection(Dir::stop);
    }

}

/**
 * handle key presses
 */
void Game::HandleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        ninja->SetDirection(Dir::left);
                        break;
                    case SDLK_RIGHT:
                        ninja->SetDirection(Dir::right);
                        break;
                    case SDLK_DOWN:
                        ninja->SetDirection(Dir::down);
                        break;
                    case SDLK_UP:
                        ninja->SetDirection(Dir::up);
                        break;
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}


/**
 * update all game objects
*/
 void Game::Update() {
    ninja->Update();
    redSamurai->SamuraiUpdate(ninja, map);
    redSamurai->Update();
    greenSamurai->SamuraiUpdate(ninja, map);
    greenSamurai->Update();
    yellowSamurai->SamuraiUpdate(ninja, map);
    yellowSamurai->Update();
}

/**
 * draw entities here
 */
void Game::Render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    ninja->PrintScores();
    ninja->Render();
    redSamurai->Render();
    greenSamurai->Render();
    yellowSamurai->Render();
    SDL_RenderPresent(renderer);

}


void Game::Clean() {

    //destroy window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = nullptr;
    renderer = nullptr;

    //quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

bool Game::Running() {
    return isRunning;
}


/**
 * inicialize all game objects
 * load map
 * set start pos for every object
 */
void Game::InitObjects() {
    map = make_shared<Map>();
    ninja = make_shared<Ninja>("./src/assets/ninja.png");
    redSamurai = make_shared<RedSamurai>("./src/assets/red_samurai.png");
    greenSamurai = make_shared<GreenSamurai>("./src/assets/green_samurai.png");
    yellowSamurai = make_shared<YellowSamurai>("./src/assets/yellow_samurai.png");
    ninja->SetStartPos(map);
    ninja->Restart();
    redSamurai->SetStartPos(map);
    redSamurai->Restart();
    greenSamurai->SetStartPos(map);
    greenSamurai->Restart();
    yellowSamurai->SetStartPos(map);
    yellowSamurai->Restart();
}

/**
 * manage mode timers and change mode
 */
void Game::Move() {
    switch (redSamurai->GetMode()) {
        case Mode::chase:
            timerForChaseMode++;
            if (timerForChaseMode == CHASE_MODE) {
                ChangeModeScatter();
            }
            break;
        case Mode::scatter:
            timerForScatterMode++;
            if (timerForScatterMode == SCATTER_MODE) {
                ChangeModeChase();
            }
            break;
        case Mode::frightened:
            timerForFrightenedMode++;
            if (timerForFrightenedMode == FRIGHTENED_MODE) {
                ChangeModeChase();
            }
            break;
        default:
            break;
    }
}

/**
 * change samurai mode to chase mode
 * reset timer for chase mode
 */
void Game::ChangeModeChase() {
    timerForChaseMode = 0;
    redSamurai->ReverseDirection();
    yellowSamurai->ReverseDirection();
    greenSamurai->ReverseDirection();
    redSamurai->ChangeChaseMode(ninja, map);
    yellowSamurai->ChangeChaseMode(ninja, map);
    greenSamurai->ChangeChaseMode(ninja, map);
}

/**
 * change samurai mode to scatter mode
 * reset timer for scatter mode
 */
void Game::ChangeModeScatter()  {
    timerForScatterMode = 0;
    redSamurai->ChangeScatterMode(map);
    yellowSamurai->ChangeScatterMode(map);
    greenSamurai->ChangeScatterMode(map);
}

/**
 * change samurai mode to frightened mode after ninja collects bonus
 * reset timer for frightened mode
 */
void Game::ChangeModeFrightened() {
    timerForFrightenedMode = 0;
    redSamurai->ChangeFrightenedMode(map);
    yellowSamurai->ChangeFrightenedMode(map);
    greenSamurai->ChangeFrightenedMode(map);
}
