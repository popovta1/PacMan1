#include "GreenSamurai.h"

/**
 * constructor for green samurai class
 * loads texture and set unique for this class parameters
 */
GreenSamurai::GreenSamurai(const char *texturesheet) : Samurai(texturesheet) {
    SleepTime = SLEEP_TIME_GREEN;
    curDir = Dir::up;
}


/**
 * Set goal coordinates for green samurai in chase mode
 * Depends on the ninja current position and ninja current direction
 * @param ninja
 * @return
 */
pair<int, int> GreenSamurai::GoalInChaseMode(shared_ptr<Ninja> ninja) const {
    pair<int, int> NinjaPos = ninja->GetCenter();
    switch (ninja->GetDir()) {
        case Dir::left:
            if (NinjaPos.first < 2) {
                return make_pair(0, NinjaPos.second) ;
            }
            return make_pair(NinjaPos.first - 2, NinjaPos.second);
        case Dir::right:
            if (NinjaPos.first + 2 >= MAP_WEIGHT) {
                return make_pair(MAP_WEIGHT - 1, NinjaPos.second);
            }
            return make_pair(NinjaPos.first + 2, NinjaPos.second);
        case Dir::down:
            if (NinjaPos.second - 2 < 0) {
                return make_pair(NinjaPos.first, 0);
            }
            return make_pair(NinjaPos.first, NinjaPos.second - 2);
        case Dir::up:
            if (NinjaPos.first + 4 >= MAP_WEIGHT || NinjaPos.second - 4 < 0) {
                return make_pair(0, 0);
            }
            return make_pair(NinjaPos.first + 4, NinjaPos.second  - 4);
        default:
            break;
    }
    return NinjaPos;
}

//down right corner is goal for green samurai in scatter mode
pair<int, int>  GreenSamurai::GoalInScatterMode() const {
    return make_pair(MAP_HEIGHT, MAP_WEIGHT);
}


//set start parameters
void GreenSamurai::SetStartPos(shared_ptr<Map> map) {
    StartPos = map->GetSamuraiPos()[1];
}
void GreenSamurai::SetStartCondition() {
    isPossibleToSamuraiRoom = true;
    SetDirection(Dir::up);
}
