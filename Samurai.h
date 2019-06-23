#include "defs.h"
#include "GameObject.h"
#include "Ninja.h"

#ifndef PAC_MAN_SAMURAI_H
#define PAC_MAN_SAMURAI_H

class Samurai : public GameObject{
public:
	 // Ты уверена, что это все public? Почему не protected?
    explicit Samurai(const char * texturesheet);
    void ChangeChaseMode(shared_ptr<Ninja> ninja, shared_ptr<Map> map);
    void ChangeScatterMode(shared_ptr<Map> map);
    void ChangeFrightenedMode(shared_ptr<Map> map);
    void ScatterMove(shared_ptr<Ninja> ninja, shared_ptr<Map> map);
    void ChaseMove(shared_ptr<Ninja> ninja);
    void FrightenedMove(shared_ptr<Ninja> ninja, shared_ptr<Map> map);
    Mode GetMode() const;
    void ChangeMode(Mode nMode);
    void WakeUp();
    void ReverseDirection();
    void SamuraiUpdate(shared_ptr<Ninja> ninja, shared_ptr<Map> map);
    virtual pair<int, int>  GoalInChaseMode(shared_ptr<Ninja> ninja) const = 0;
    virtual pair<int, int>  GoalInScatterMode() const = 0;
    bool IsWait() const;
    virtual void SetStartCondition() = 0;
    void Restart();
    void SetGoal(pair<int, int> NinjaPos);
    virtual void SetStartPos(shared_ptr<Map> map) = 0;
protected:
    pair<int, int> NextStep;
    Dir newDir;
    pair<int, int> goal;
    Mode curMode;
    Mode prevMode;
    int SleepTime;
    int timerForWakeUp;
    pair<int, int> leftdown;
    pair<int, int> rightdown;
    pair<int, int> leftup;
    pair<int, int> rightup;
    bool isPossibleToSamuraiRoom;
    bool wait;
    void EqPosition();
    void SetNextStep(shared_ptr<Map> map);
    void SetBeforeNextStep();
    void Collision(shared_ptr<Ninja> ninja);
    pair<int, int> GoalInFrightenedMode();
    void LeaveRoom(shared_ptr<Map> map, shared_ptr<Ninja> ninja);
    void MoveAlgorithm(shared_ptr<Map>  map);
    double DistLeft(const vector<vector<shared_ptr<Map_object>>> &map) const;
    double DistRight(const vector<vector<shared_ptr<Map_object>>> &map) const;
    double DistForward(const vector<vector<shared_ptr<Map_object>>> &map) const;
    double DistBackward(const vector<vector<shared_ptr<Map_object>>> &map) const;
    shared_ptr<Map_object> GetLeft(vector<vector<shared_ptr<Map_object>>> const & map) const;
    shared_ptr<Map_object> GetRight(vector<vector<shared_ptr<Map_object>>> const & map) const;
    shared_ptr<Map_object> GetForward(vector<vector<shared_ptr<Map_object>>> const & map) const;
    shared_ptr<Map_object> GetBackward(vector<vector<shared_ptr<Map_object>>> const & map) const;

};
#endif //PAC_MAN_SAMURAI_H
