#include "Samurai.h"
#ifndef PAC_MAN_REDSAMURAI_H
#define PAC_MAN_REDSAMURAI_H

class RedSamurai : public Samurai{
public:
    explicit RedSamurai(const char * texturesheet);
    pair<int, int> GoalInChaseMode(shared_ptr<Ninja> ninja) const;
    pair<int, int>  GoalInScatterMode() const;
    void SetStartPos(shared_ptr<Map> map);
    void SetStartCondition();
};
#endif //PAC_MAN_REDSAMURAI_H
