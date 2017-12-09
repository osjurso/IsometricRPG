
#ifndef ISORPG_COMPCOST_H
#define ISORPG_COMPCOST_H

#include <anax/Component.hpp>

#include "states/state_base.h"


struct CostComponent : public anax::Component
{
public:
    int ArmorUpgrade;
    int WeaponUpgrade;
};

#endif //ISORPG_COMPCOST_H
