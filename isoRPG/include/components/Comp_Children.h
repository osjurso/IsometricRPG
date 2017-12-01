

#ifndef ISORPG_COMP_CHILDREN_H
#define ISORPG_COMP_CHILDREN_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct ChildComponent : public anax::Component
{
public:

    std::vector<anax::Entity> children;
};


#endif //ISORPG_COMP_CHILDREN_H
