#include "YellowSamurai.h"
/**
 * constructor for yellow samurai class
 * loads texture and set unique for this class parameters
 */
YellowSamurai::YellowSamurai(const char *texturesheet) : Samurai(texturesheet) {
    SleepTime = SLEEP_TIME_YELLOW;
    curDir = Dir::up;
}


/**
 * Set goal coordinates for yellow samurai in chase mode
 * Depends on the distance from ninja
 * @param ninja
 * @return
 */
pair<int, int> YellowSamurai::GoalInChaseMode(shared_ptr<Ninja> ninja) const {
    double dist = DistFromNinja(ninja);
    if (dist > DIST_TO_NINJA) {
        return ninja->GetCenter();
    }
    return GoalInScatterMode();
}

//up right corner is goal for yellow samurai in scatter mode
pair<int, int>  YellowSamurai::GoalInScatterMode() const {
    return make_pair(0, MAP_WEIGHT);
}


//set start parameters
void YellowSamurai::SetStartPos(shared_ptr<Map> map) {
    StartPos = map->GetSamuraiPos()[3];
}

void YellowSamurai::SetStartCondition() {
    isPossibleToSamuraiRoom = true;
}

/**
 * compute distance from ninja
 * @param ninja
 * @return
 */
double YellowSamurai::DistFromNinja(shared_ptr<Ninja> ninja) const {
    return Dist(GetCenter().first, ninja->GetCenter().first, GetCenter().second, ninja->GetCenter().second);
}
