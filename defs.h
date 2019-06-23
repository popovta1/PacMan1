//file for inicialisation global variables and functions
#include <cmath>
#include <string>
#include <iostream>
#include <utility>
#ifndef PAC_MAN_DEFS_H
#define PAC_MAN_DEFS_H
using namespace std;

const double  MAX_DIST = 10000;
const int SCREEN_WEIGHT = 800;
const int SCREEN_HEIGHT = 800;

const int MAP_WEIGHT = 20;
const int MAP_HEIGHT = 20;

const int NINJA_SIZE_W = 38;
const int NINJA_SIZE_H = 38;

const int GRASS_SIZE_W = 40;
const int GRASS_SIZE_H = 40;
const int GRASS_IMAGE_SIZE_W = 32;
const int GRASS_IMAGE_SIZE_H = 32;

const int SAKURA_SIZE_W = 20;
const int SAKURA_SIZE_H = 20;

const int PANCAKE_SIZE_W = 30;
const int PANCAKE_SIZE_H = 30;
const int PANCAKE_IMAGE_SIZE_W = 512;
const int PANCAKE_IMAGE_SIZE_H = 512;

const int SAMURAI_SIZE_W = 40;
const int SAMURAI_SIZE_H = 40;

const int OBJECT_SIZE_W = 40;
const int OBJECT_SIZE_H = 40;
const int NUMBER_OF_LINEES_IN_INPUT = 10;
const int SPECIFIC_NUM_SAKURA = 10;
const int SPECIFIC_NUM_PANCAKE = 5;
const int DIST_TO_NINJA = 8;
extern int NINJA_SPEED;
extern int SPEED_IN_CHASE_MODE;
extern int SPEED_IN_SCATTER_MODE;
extern int SPEED_IN_FRIGHTENED_MODE;
extern int SLEEP_TIME_RED;
extern int SLEEP_TIME_GREEN;
extern int SLEEP_TIME_YELLOW;
extern int CHASE_MODE;
extern int SCATTER_MODE;
extern int FRIGHTENED_MODE;
enum Dir {
    left, right, up, down, stop
};

enum Mode {
    chase, scatter, frightened
};

enum Type {
    grass, sakura, pancake
};

double Dist(int x1, int y1, int x2, int y2);

bool SortByFirst(const pair<double, Dir> & a, const pair<double, Dir> & b);


#endif //PAC_MAN_DEFS_H
