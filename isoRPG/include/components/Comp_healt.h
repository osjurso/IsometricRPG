#ifndef ISORPG_COMP_HEALT_H
#define ISORPG_COMP_HEALT_H

#include <anax/Component.hpp>

#include "states/state_base.h"

class HealthComponent : public anax::Component
{
public:
    int health;
    int maxHealth;
};

#endif //ISORPG_COMP_HEALT_H
