#include "Samurai.h"
#ifndef PAC_MAN_GREENSAMURAI_H
#define PAC_MAN_GREENSAMURAI_H
class GreenSamurai : public Samurai{
public:
    GreenSamurai(const char * texturesheet);
    pair<int, int> GoalInChaseMode(shared_ptr<Ninja> ninja) const;
    pair<int, int>  GoalInScatterMode() const;
    void SetStartPos(shared_ptr<Map> map);
    void SetStartCondition();
};
#endif //PAC_MAN_GREENSAMURAI_H
