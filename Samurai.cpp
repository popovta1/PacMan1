#include <iostream>
#include "Samurai.h"
#include <algorithm>
#include <cassert>

vector<pair<double, Dir>> Directions;
int m = 0;

/**
 * constructor for virtual class
 * set common for all samurai types parameters
 * @param texturesheet
 */
Samurai::Samurai(const char *texturesheet) : GameObject(texturesheet) {
    destRec.w = SAMURAI_SIZE_W;
    destRec.h = SAMURAI_SIZE_H;
    newDir = Dir::stop;
    timerForWakeUp = 0;
    wait = true;
}
/**
 * distance from next samurai step and samurai current goal
 * different methods for different sides
 * @param map
 * @return
 */

double Samurai::DistLeft(const vector<vector<shared_ptr<Map_object>>> &map) const {
    Type type;
    if (GetLeft(map) != nullptr) {
        type = GetLeft(map)->GetType();
    } else {
        return Dist(NextStep.first - 1, NextStep.second, goal.first, goal.second);
    }
    if (type != Type::grass) {
        return Dist(NextStep.first - 1, NextStep.second, goal.first, goal.second);
    }
    return MAX_DIST;
}

double Samurai::DistRight(const vector<vector<shared_ptr<Map_object>>> &map) const {
    Type type;
    if (GetRight(map) != nullptr) {
        type = GetRight(map)->GetType();
    } else {
        return Dist(NextStep.first + 1, NextStep.second, goal.first, goal.second);
    }
    if (type != Type::grass) {
        return Dist(NextStep.first + 1, NextStep.second, goal.first, goal.second);
    }
    return MAX_DIST;
}

double Samurai::DistForward(const vector<vector<shared_ptr<Map_object>>> &map) const {
    Type type;
    if (GetForward(map) != nullptr) {
        type = GetForward(map)->GetType();
    } else {
        return Dist(NextStep.first, NextStep.second - 1, goal.first, goal.second);
    }
    if (type != Type::grass) {
        return Dist(NextStep.first, NextStep.second - 1, goal.first, goal.second);
    }
    return MAX_DIST;
}

double Samurai::DistBackward(const vector<vector<shared_ptr<Map_object>>> &map) const {
    Type type;
    if (GetBackward(map) != nullptr) {
        type = GetBackward(map)->GetType();
    } else {
        return Dist(NextStep.first, NextStep.second + 1, goal.first, goal.second);
    }
    if (type != Type::grass) {
        return Dist(NextStep.first, NextStep.second + 1, goal.first, goal.second);
    }
    return MAX_DIST;
}


/**
 * getters for different sides of next  samurai step
 * @param map
 * @return
 */


shared_ptr<Map_object> Samurai::GetLeft(vector<vector<shared_ptr<Map_object>>> const &map) const {
    return map[NextStep.second][NextStep.first - 1];
}

shared_ptr<Map_object> Samurai::GetRight(vector<vector<shared_ptr<Map_object>>> const &map) const {
    return map[NextStep.second][NextStep.first + 1];
}

shared_ptr<Map_object> Samurai::GetForward(vector<vector<shared_ptr<Map_object>>> const &map) const {
    return map[NextStep.second - 1][NextStep.first];
}

shared_ptr<Map_object> Samurai::GetBackward(vector<vector<shared_ptr<Map_object>>> const &map) const {
    return map[NextStep.second + 1][NextStep.first];
}

//update goal in chase mode(because ninja is moving)
void Samurai::ChaseMove(shared_ptr<Ninja> ninja) {
    SetGoal(GoalInChaseMode(ninja));
}


//set parameters for chase mode
void Samurai::ChangeChaseMode(shared_ptr<Ninja> ninja, shared_ptr<Map> map) {
    ChangeMode(Mode::chase);
    EqPosition();
    SetSpeed(SPEED_IN_CHASE_MODE);
    SetGoal(GoalInChaseMode(ninja));
    SetBeforeNextStep();
    SetNextStep(map);
}

//set parameters for scatter mode
void Samurai::ChangeScatterMode(shared_ptr<Map> map) {
    if(!isPossibleToSamuraiRoom) {
        ChangeMode(Mode::scatter);
        EqPosition();
        ReverseDirection();
        SetSpeed(SPEED_IN_SCATTER_MODE);
        SetGoal(GoalInScatterMode());
        SetBeforeNextStep();
        SetNextStep(map);
    }
}


//set parameters for frightened mode
void Samurai::ChangeFrightenedMode(shared_ptr<Map> map) {
    ChangeMode(Mode::frightened);
    EqPosition();
    SetSpeed(SPEED_IN_FRIGHTENED_MODE);
    ReverseDirection();
    SetGoal(make_pair(10, 10));
    SetBeforeNextStep();
    SetNextStep(map);
}


/**
 * set new direction
 * direction for after next step
 * it is minimum from all distance from next step to current goal
 * also it could not be opposite for currwnt direction
 * @param curMap
 */

void Samurai::SetNextStep(shared_ptr<Map> curMap) {
    vector<vector<shared_ptr<Map_object>>> map = curMap->GetMap();
    double Left = DistLeft(map);
    double Right = DistRight(map);
    double Forward = DistForward(map);
    double Backward = DistBackward(map);
    switch (curDir) {
        case Dir::left:
            Right = MAX_DIST;
            break;
        case Dir::right:
            Left = MAX_DIST;
            break;
        case Dir::up:
            Backward = MAX_DIST;
            break;
        case Dir::down:
            Forward = MAX_DIST;
            break;
        default:
            break;

    }
    Directions.resize(4);
    /**
     * vector with directions and distance to goal by this direction
     */

    Directions = {make_pair(Left, Dir::left), make_pair(Right, Dir::right),
                  make_pair(Forward, Dir::up), make_pair(Backward, Dir::down)};
    sort(Directions.begin(), Directions.end(), SortByFirst);
    for (int i = 0; i < 4; i++) {
        Dir oldDir = curDir;
        SetDirection(Directions[i].second);
        if (IsPossible(curMap) && (!CollisionSamuraiRoom(curMap) || isPossibleToSamuraiRoom)) {
            newDir = Directions[i].second;
            SetDirection(oldDir);
            m = i;
            return;
        }

    }

}


/**
 * next samurai step depends on the current direction
 * @param curMap
 */

void Samurai::SetBeforeNextStep() {
    int x = GetCenter().first;
    int y = GetCenter().second;
    switch (curDir) {
        case Dir::left:
            NextStep = make_pair(x - 1, y);
            break;
        case Dir::right:
            NextStep = make_pair(x + 1, y);
            break;
        case Dir::up:
            NextStep = make_pair(x, y - 1);
            break;
        case Dir::down:
            NextStep = make_pair(x, y + 1);
            break;
        default:
           assert(false);
    }
}


void Samurai::MoveAlgorithm(shared_ptr<Map> map) {
    Teleport();
    /**
     * if samurai came move in the current direction and
     * he is not at the next step, then move
     */
    bool NotReachNextStep = (GetDownRightCorner() != NextStep) || (GetUpLeftCorner() != NextStep);
    bool CollisionWithSamuraiRoom = !isPossibleToSamuraiRoom && CollisionSamuraiRoom(map);
    if (NotReachNextStep && IsPossible(map) && !CollisionWithSamuraiRoom && map->IfPossibleToMove(NextStep)) {
        Move();
    } else {
        if (GetCenter() == goal) {
            return;
        }
        /**
         * if samurai can not move in its direction then change direction to the next minimum
         */
        if (!IsPossible(map) || CollisionWithSamuraiRoom || !map->IfPossibleToMove(NextStep)) {
            newDir = Directions[(m + 1) / 3].second;
            curDir = newDir;
            SetBeforeNextStep();
        }
        else {
            SetNextStep(map);
            SetDirection(newDir);
            SetBeforeNextStep();
        }
    }
}

/**
 * Set samurai to the start position
 * set start parameters
 */
void Samurai::Restart() {
    xpos = StartPos.first;
    ypos = StartPos.second;
    SetStartCondition();

}

/**
 * Each samurai wakes up and begin to move after unique time
 */
void Samurai::WakeUp() {
    timerForWakeUp = 0;
    SetSpeed(SPEED_IN_CHASE_MODE);
    curMode = Mode::chase;
    wait = false;

}

void Samurai::EqPosition() {
    pair<int, int> center = GetCenter();
     xpos = (center.first) * 40 ;
    ypos = (center.second) * 40 ;

}

//change current goal
void Samurai::SetGoal(pair<int, int> NinjaPos) {
    goal = NinjaPos;
}

bool Samurai::IsWait() const {
    return wait;
}


/**
 * find and manage collision with ninja
 * @param ninja
 */
void Samurai::Collision(shared_ptr<Ninja> ninja) {
    if (GetCenter() == ninja->GetCenter()) {
        switch (curMode) {
            case Mode::chase:
                Restart();
                wait = true;
                ninja->Restart();
                ninja->AddScore(-10);
                break;
            case Mode::scatter:
                Restart();
                break;
            case Mode::frightened:
                Restart();
                wait = true;
                timerForWakeUp = 0;
                ninja->AddScore(100);
                break;
            default:
                break;
        }
    }
}


void Samurai::ChangeMode(Mode nMode) {
    curMode = nMode;
}


Mode Samurai::GetMode() const {
    return curMode;
}

/**
 * change direction to the opposite
 */
void Samurai::ReverseDirection() {
    switch (curDir) {
        case Dir::left:
            SetDirection(Dir::right);
            break;
        case Dir::right:
            SetDirection(Dir::left);
            break;
        case Dir::up:
            SetDirection(Dir::down);
            break;
        case Dir::down:
            SetDirection(Dir::up);
            break;
        default:
            break;
    }
}

void Samurai::LeaveRoom(shared_ptr<Map> map, shared_ptr<Ninja> ninja) {
    if (GetUpLeftCorner() == goal && GetDownRightCorner() == goal) {
        isPossibleToSamuraiRoom = false;
        ChangeChaseMode(ninja, map);
    } else {
        MoveAlgorithm(map);
    }
}

/**
 * Update samurai position and direction
 * @param ninja
 * @param map
 */
void Samurai::SamuraiUpdate(shared_ptr<Ninja> ninja, shared_ptr<Map> map) {
    if (IsWait()) {
        timerForWakeUp++;
    }
    if (timerForWakeUp == SleepTime) {
        WakeUp();
        if (isPossibleToSamuraiRoom) {
            SetGoal(make_pair(map->GetSamuraiRoom().first, map->GetSamuraiRoom().second - 1));
        }
        SetBeforeNextStep();
        SetNextStep(map);
    }
    if (!wait) {
        if (isPossibleToSamuraiRoom) {
            LeaveRoom(map, ninja);
        } else {
            switch (curMode) {
                case Mode::chase:
                    ChaseMove(ninja);
                    break;
                default:
                    break;
            }
            
            MoveAlgorithm(map);
            Collision(ninja);
        }
    }
}
