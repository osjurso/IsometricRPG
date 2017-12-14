#ifndef ISORPG_COMP_LOOTEBLE_H
#define ISORPG_COMP_LOOTEBLE_H

#include <anax/Component.hpp>

#include "states/state_base.h"

class Lootable : public anax::Component
{
public:
    int gold;
    int HealthPotion;
    int armorModifier  = 0;
    int weaponModifier = 0;
    int armor = 0;
    int weapon = 10;
    std::string name;
};


#endif //ISORPG_COMP_LOOTEBLE_H
