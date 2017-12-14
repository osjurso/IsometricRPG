#ifndef ISORPG_COMP_PARENT_H
#define ISORPG_COMP_PARENT_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct ParentComponent : public anax::Component
{
public:

    anax::Entity parent;
};

#endif //ISORPG_COMP_PARENT_H
