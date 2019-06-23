#include "Map.h"
#include <iostream>
#include "game.h"
#include "TextureManager.h"
#include "fstream"
#include "Grass.h"
#include "Sakura.h"
#include "Pancake.h"
#include "sstream"

/**
 * constructor sets default parameters and loads the map from file
 */
Map::Map() {
    ninjaPos = make_pair(0, 0);
    map.resize(MAP_HEIGHT);
    maxScore = 0;
    LoadMap("./src/map.txt");
}

/**
 * read game difficulty, objects speed and other parameters from file
 * @param file
 */
void Map::SetDifficulty(ifstream & file) {
    if (!file.is_open()) {
        throw std::logic_error("Can not open the file!");
    }
    int num = 0;
    stringstream s;
    string str;
    /**
     * get numbers from file lines
     */
    while (num != NUMBER_OF_LINEES_IN_INPUT) {
        getline(file, str);
        stringstream ss;
        ss << str;
        string temp;
        int found;
        while (!ss.eof()) {
            ss >> temp;
            if (stringstream(temp) >> found)
                s << found << ' ';
            temp = "";
        }
        num++;
    }
    s >> NINJA_SPEED >> SPEED_IN_CHASE_MODE >> SPEED_IN_SCATTER_MODE
      >> SPEED_IN_FRIGHTENED_MODE
      >> CHASE_MODE >> SCATTER_MODE >> FRIGHTENED_MODE
      >> SLEEP_TIME_RED >> SLEEP_TIME_GREEN
      >> SLEEP_TIME_YELLOW;

}
/**
 * load map for game from .txt file
 * @param filename
 */
void Map::LoadMap(const string &filename) {
    std::ifstream file;
    file.open(filename);
    if (!file.good()) {
        throw std::logic_error("Can not open the file!");
    }
    SetDifficulty(file);
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int column = 0; column < MAP_WEIGHT; column++) {
            char c;
            file >> c;
            switch (c) {
                case '1': //grass on the map
                    map[row].push_back(make_shared<Grass>("./src/assets/grass.png"));
                    map[row][column]->SetDest(column * OBJECT_SIZE_W, row * OBJECT_SIZE_H);
                    break;
                case '0': // coints on the map
                    map[row].push_back(make_shared<Sakura>("./src/assets/sakura.png"));
                    maxScore ++;
                    map[row][column]->SetDest(column * OBJECT_SIZE_W + SPECIFIC_NUM_SAKURA,
                                              row * OBJECT_SIZE_H + SPECIFIC_NUM_SAKURA);
                    break;
                case '3': // bonuses on the map
                    map[row].push_back(make_shared<Pancake>("./src/assets/pancake.png"));
                    maxScore += 10;
                    map[row][column]->SetDest(column * OBJECT_SIZE_W + SPECIFIC_NUM_PANCAKE,
                                              row * OBJECT_SIZE_H + SPECIFIC_NUM_PANCAKE);
                    break;
                case 'x': // position of the entrance to the samurai room
                    map[row].push_back(nullptr);
                    SamuraiRoom = make_pair(column, row);
                    break;
                case 'N': // ninja start position
                    map[row].push_back(nullptr);
                    if (ninjaPos == make_pair(0, 0)) {
                        ninjaPos = make_pair(column * OBJECT_SIZE_W, row * OBJECT_SIZE_H);
                    }
                    break;
                case 'S': //samurai start positions
                    map[row].push_back(nullptr);
                    SamuraiPos.emplace_back(column * OBJECT_SIZE_H, row * OBJECT_SIZE_W);
                    break;
                default:
                    map[row].push_back(nullptr);
                    break;
            }
        }
    }
    file.close();
}
/**
 * draw map with map objects
 */
void Map::DrawMap() {
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int column = 0; column < MAP_WEIGHT; column++) {
            if (map[row][column] != nullptr) {
                map[row][column]->Draw();
            }
        }
    }
}

//getter for map class
vector<vector<shared_ptr<Map_object>>> Map::GetMap() const {
    return map;
}

/**
 * when ninja collects coins, they removes from the map
 * @param x
 * @param y
 */
void Map::RemovePoint(int x, int y) {
    if (map[x][y] != nullptr) {
        map[x][y]->Delete();
        map[x][y] = nullptr;
    }
}

/**
 * getters for start game objects positions and samurai room entrance
 * @return
 */
pair<int, int> Map::GetNinjaPos() const {
    return ninjaPos;
}

pair<int, int> Map::GetSamuraiRoom() const {
    return SamuraiRoom;
}

vector<pair<int, int>> Map::GetSamuraiPos() const {
    return SamuraiPos;
}

int Map::GetMaxScore() const {
    return maxScore;
}

bool Map::IfPossibleToMove(pair<int, int> pos) const {
    return !((map[pos.second][pos.first] != nullptr) &&
            (map[pos.second][pos.first]->GetType() == Type::grass)) ||
                    make_pair(pos.first,pos.second) == SamuraiRoom;
}


/**
 * check type ob the map object at the coordinates
 * @param pos
 * @return
 */
bool Map::IfSakura(pair<int, int> pos) const {
    return map[pos.second][pos.first] != nullptr &&
           map[pos.second][pos.first]->GetType() == Type::sakura;
}
bool Map::IfPancake(pair<int, int> pos) const {
    return map[pos.second][pos.first] != nullptr &&
           map[pos.second][pos.first]->GetType() == Type::pancake;
}
