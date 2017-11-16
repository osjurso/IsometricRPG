
#ifndef ISORPG_COMP_TALK_H
#define ISORPG_COMP_TALK_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct Talkative : public anax::Component
{
public:
    std::map<int, std::string> files;
    int numberOfDialoges = 0;
};

#endif //ISORPG_COMP_TALK_H
