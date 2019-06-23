#include <cmath>
#include <fstream>
#include "defs.h"
#include <sstream>

double Dist(int x1, int y1, int x2, int y2) { 
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


bool SortByFirst(const pair<double, Dir> &a, const pair<double, Dir> &b) {
    return a.first < b.first;
}


int NINJA_SPEED = 0;
int SPEED_IN_CHASE_MODE = 0;
int SPEED_IN_SCATTER_MODE = 0;
int SPEED_IN_FRIGHTENED_MODE = 0;
int SLEEP_TIME_RED = 0;
int SLEEP_TIME_GREEN = 0;
int SLEEP_TIME_YELLOW = 0;
int CHASE_MODE = 0;
int SCATTER_MODE = 0;
int FRIGHTENED_MODE = 0;
