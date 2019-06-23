#include "RedSamurai.h"

/**
 * constructor for red samurai class
 * loads texture and set unique for this class parameters
 */
RedSamurai::RedSamurai(const char *texturesheet) : Samurai(texturesheet) {
    curDir = Dir::left;
    SleepTime = SLEEP_TIME_RED;
}

//goal for red samurai in chase mode is ninja coordinates
pair<int, int> RedSamurai::GoalInChaseMode(shared_ptr<Ninja> ninja) const {
    return ninja->GetCenter();
}

//goal for red samurai in scatter mode is left up corner
pair<int, int>  RedSamurai::GoalInScatterMode() const {
    return make_pair(0, 0);
}


//set start parameters
void RedSamurai::SetStartPos(shared_ptr<Map> map) {
    StartPos = map->GetSamuraiPos()[0];
}

void RedSamurai::SetStartCondition() {
    isPossibleToSamuraiRoom = false;
    SetDirection(Dir::left);
}
