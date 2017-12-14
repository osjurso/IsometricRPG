#ifndef ISORPG_COMP_SAVE_H
#define ISORPG_COMP_SAVE_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct SaveComponent : public anax::Component
{
public:
    std::string file;
    int number = -1;
};

#endif //ISORPG_COMP_SAVE_H
