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
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect spriteRect;
    int pixles;
};

#endif //ISORPG_COMP_TEXTURE_H
