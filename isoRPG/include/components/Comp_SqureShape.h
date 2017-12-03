
#ifndef ISORPG_COMP_SQURESHAPE_H
#define ISORPG_COMP_SQURESHAPE_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct SqureComponent : public anax::Component
{
public:
    sf::RectangleShape rectShape;
};

#endif //ISORPG_COMP_SQURESHAPE_H
