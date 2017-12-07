
#ifndef ISORPG_COMP_TALK_H
#define ISORPG_COMP_TALK_H

#include <anax/Component.hpp>

#include "states/state_base.h"

typedef void (*pfunc)(anax::Entity&, anax::Entity&, anax::World&);

struct Talkative : public anax::Component
{
public:
    std::map<int, std::string> talkingfiles;
    std::map<int, std::string> optionMap;
    std::map<int, pfunc> functionmap;
    std::map<int, int> total;

    std::map<int, std::map<int,std::string>> options;
    std::map<int, std::map<int,pfunc>> functions;

    int Current = 0 ;
    int Default = -1;
    int TotalOfDialogs = -1;
    bool activeDialog = false;
    bool changeDialog = false;

};

#endif //ISORPG_COMP_TALK_H
