#ifndef ISORPG_COMP_ACTIONTIMERS_H
#define ISORPG_COMP_ACTIONTIMERS_H


#include <anax/Component.hpp>

#include "states/state_base.h"

class ActionTimer : public anax::Component
{
public:
    float AttackCooldown;
    float PotionCooldown;
    sf::Clock AttackTimer;
    sf::Clock PotionTimer;
};

#endif //ISORPG_COMP_ACTIONTIMERS_H
