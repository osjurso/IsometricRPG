#ifndef ISORPG_COMP_HEALT_H
#define ISORPG_COMP_HEALT_H

#include <anax/Component.hpp>

#include "states/state_base.h"

class HealthComponent : public anax::Component
{
public:
    float health;
    float maxHealth;
    int totalKills;
    int unpaidKills;
    int attackRange;
};

#endif //ISORPG_COMP_HEALT_H
