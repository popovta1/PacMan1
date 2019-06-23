
#include "GameObject.h"
#include "TextureManager.h"
using namespace std;

/**
 * constructor sets default position and speed of game object
 * loads texture
 * @param texturesheet
 */
GameObject::GameObject(const char *texturesheet) : xpos(0), ypos(0), speed(0) {
    objTexture = TextureManager::LoadTexture(texturesheet);
}

/**
 * game object sets new own direction
 * @param newDir
 */
void GameObject::SetDirection(Dir newDir) {
    curDir = newDir;
}

GameObject::~GameObject() {
    SDL_DestroyTexture(objTexture);
}

/**
 * draw game object
 */
void GameObject::Render() {
    TextureManager::Draw(objTexture, destRec);
}

/**
 * game object changes its position
 * @param newPos
 */
void GameObject::SetPos(pair<int, int> newPos) {
    xpos = newPos.first;
    ypos = newPos.second;
}


/**
 * game object changes its position py certain direction
 */
void GameObject::BackwardMove() {
    ypos += speed;
}

void GameObject::LeftDir() {
    xpos -= speed;
}

void GameObject::RightDir() {
    xpos += speed;
}

void GameObject::ForwardMove() {
    ypos -= speed;
}


//getter for game objects direction
Dir GameObject::GetDir() const {
    return curDir;
}

/**
 * game object moves depending on the current direction
 */
void GameObject::Move() {
    Teleport();
    switch (curDir) {
        case Dir::left:
            LeftDir();
            break;
        case Dir::right:
            RightDir();
            break;
        case Dir::up:
            ForwardMove();
            break;
        case Dir::down:
            BackwardMove();
            break;
        default:
            break;
    }
}

/**
 * get the coordinates of the different parts of the object on the map
 * @return
 */
pair<int, int> GameObject::GetDownLeftCorner() const {
    return make_pair(xpos / OBJECT_SIZE_W, (ypos + OBJECT_SIZE_H - 1) / OBJECT_SIZE_H);
}

pair<int, int> GameObject::GetDownRightCorner() const {
    return make_pair((xpos + OBJECT_SIZE_W - 1) / OBJECT_SIZE_W, (ypos + OBJECT_SIZE_H - 1) / OBJECT_SIZE_H);
}

pair<int, int> GameObject::GetUpLeftCorner() const {
    return make_pair(xpos / OBJECT_SIZE_W, ypos / OBJECT_SIZE_H);
}

pair<int, int> GameObject::GetUpRightCorner() const {
    return make_pair((xpos + OBJECT_SIZE_W - 1) / OBJECT_SIZE_W, ypos / OBJECT_SIZE_H);
}

pair<int, int> GameObject::GetCenter() const {
    return make_pair((xpos + OBJECT_SIZE_W / 2) / OBJECT_SIZE_W,
                     (ypos + OBJECT_SIZE_H / 2) / OBJECT_SIZE_H);
}


//set new game objects speed
void GameObject::SetSpeed(int newSpeed) {
    speed = newSpeed;
}

/**
 * move in certain direction
 * @param dir
 */
void GameObject::Move(Dir dir) {
    SetDirection(dir);
    Move();
}

/**
 * set new coordinats of game object on the window
 */
void GameObject::Update() {
    destRec.x = xpos;
    destRec.y = ypos;
}

/**
 * check collision game object and grass
 * @param map
 * @return
 */

bool GameObject::IsPossible(shared_ptr<Map> map) {
    vector<vector<shared_ptr<Map_object>>> curMap = map->GetMap();
    for (unsigned int i = 0; i < curMap.size(); i++) {
        for (unsigned int j = 0; j < curMap[i].size(); j++) {
            if (curMap[i][j] != nullptr && curMap[i][j]->GetType() == Type::grass) {
                /**
                 * I check just part of object the first could intersect with grass
                 */
                switch (curDir) {
                    case Dir::left:
                        if (GetDownLeftCorner() == make_pair<int, int>(j, i) ||
                            GetUpLeftCorner() == make_pair<int, int>(j, i)) {
                            RightDir();
                            return false;
                        }
                        break;
                    case Dir::right:
                        if (GetDownRightCorner() == make_pair<int, int>(j, i) ||
                            GetUpRightCorner() == make_pair<int, int>(j, i)) {
                            LeftDir();
                            return false;
                        }
                        break;
                    case Dir::down:
                        if (GetDownLeftCorner() == make_pair<int, int>(j, i) ||
                            GetDownRightCorner() == make_pair<int, int>(j, i)) {
                            ForwardMove();
                            return false;
                        }
                        break;
                    case Dir::up:
                        if (GetUpRightCorner() == make_pair<int, int>(j, i) ||
                            GetUpLeftCorner() == make_pair<int, int>(j, i)) {
                            BackwardMove();
                            return false;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return true;
}
/**
 * Every map edge is a portal
 * If objects crosses any edge, it will teleport to the opposite map edge
 */
void GameObject::Teleport() {
    switch (curDir) {
        case Dir::left:
            if (xpos == 0) {
                xpos = SCREEN_WEIGHT - 50;
            }
            break;
        case Dir::right:
            if (xpos == SCREEN_WEIGHT - 50) {
                xpos = 0;
            }
            break;
        case Dir::up:
            if (ypos == 0) {
                ypos = SCREEN_HEIGHT - 50;
            }
            break;
        case Dir::down:
            if (ypos == SCREEN_HEIGHT - 50) {
                ypos = 0;
            }
            break;
        default:
            break;
    }
}

/**
 * object can not enter the samurai room
 * this method checks collision with enter to the samurai room
 * @param map
 * @return
 */
bool GameObject::CollisionSamuraiRoom(shared_ptr<Map> map) {
    pair<int, int> room = map->GetSamuraiRoom();
    switch (curDir) {
        case Dir::left:
            if (GetDownLeftCorner() == room ||
                GetUpLeftCorner() == room) {
                RightDir();
                return true;
            }
            break;
        case Dir::right:
            if (GetDownRightCorner() == room ||
                GetUpRightCorner() == room) {
                LeftDir();
                return true;
            }
            break;
        case Dir::down:
            if (GetDownLeftCorner() == room ||
                GetDownRightCorner() == room) {
                ForwardMove();
                return true;
            }
            break;
        case Dir::up:
            if (GetUpRightCorner() == room ||
                GetUpLeftCorner() == room) {
                BackwardMove();
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}
