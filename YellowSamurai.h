#include "Samurai.h"
#ifndef PAC_MAN_YELLOWSAMURAI_H
#define PAC_MAN_YELLOWSAMURAI_H
class YellowSamurai : public Samurai{
public:
    YellowSamurai(const char * texturesheet);
    pair<int, int> GoalInChaseMode(shared_ptr<Ninja> ninja) const;
    pair<int, int>  GoalInScatterMode() const;
    void SetStartPos(shared_ptr<Map> map);
    void SetStartCondition();
    double DistFromNinja(shared_ptr<Ninja> ninja) const;
};
#endif //PAC_MAN_YELLOWSAMURAI_H
