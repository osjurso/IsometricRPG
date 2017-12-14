#ifndef ISORPG_COMP_CHANGEBLE_H
#define ISORPG_COMP_CHANGEBLE_H


#include <anax/Component.hpp>

#include "states/state_base.h"

struct ChangeableComponent : public anax::Component
{
public:
    bool changeble;
    float max;
    float min;
    float current;
    std::string source;
};

#endif //ISORPG_COMP_CHANGEBLE_H
