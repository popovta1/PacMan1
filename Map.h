#include "game.h"
#include "defs.h"
#include <string>
#include "Map_object.h"
#include <vector>
#include "defs.h"

#ifndef MAP_H
#define MAP_H
using namespace std;
class Map {
public:

    Map();

    void DrawMap();
    pair<int, int> GetNinjaPos() const;
    void RemovePoint(int x, int y);
    bool IfPossibleToMove(pair<int, int> pos) const;
    bool IfSakura(pair<int, int> pos) const;
    bool IfPancake(pair<int, int> pos) const;
    vector<vector<shared_ptr<Map_object>>> GetMap() const;
    pair<int, int> GetSamuraiRoom() const;
    vector<pair<int, int>> GetSamuraiPos() const;
    int GetMaxScore() const;
private:
    int maxScore;
    void LoadMap(const string& filename);
    void SetDifficulty(ifstream & file);
    pair<int, int> ninjaPos;
    pair<int, int> SamuraiRoom;
    vector<pair<int, int>> SamuraiPos;
    vector<vector<shared_ptr<Map_object>>> map;
};

#endif //MAP_H
