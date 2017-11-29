
#ifndef ISORPG_COMP_TALK_H
#define ISORPG_COMP_TALK_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct Talkative : public anax::Component
{
public:
    std::map<int, std::string> Talkingfiles;
    std::map<int, std::string> Optoinfiles;
    int numberOfDialoges = 0;
    int numberOfOption = 0;
    int DialogCurent = 0 ;
    int OptionCurent = 0 ;
};

#endif //ISORPG_COMP_TALK_H
