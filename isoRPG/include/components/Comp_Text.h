
#ifndef ISORPG_COMP_TEXT_H
#define ISORPG_COMP_TEXT_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct TextComponent : public anax::Component
{
public:

    sf::Text text;
    sf::Font font;
    std::string content;
    bool draw = true;

};

#endif //ISORPG_COMP_TEXT_H
