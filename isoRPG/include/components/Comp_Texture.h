//
// Created by Bjornar on 02.11.2017.
//

#ifndef ISORPG_COMP_TEXTURE_H
#define ISORPG_COMP_TEXTURE_H

#include <anax/Component.hpp>

#include "states/state_base.h"

struct TextureComponent : public anax::Component
{
public:

    sf::Texture texture[4];
    sf::Sprite sprite[4];
    sf::IntRect spriteRect;
    bool multisprite = false;
};

#endif //ISORPG_COMP_TEXTURE_H
