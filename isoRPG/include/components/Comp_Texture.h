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

    sf::Texture tHeroBody;
    sf::Texture tHeroHead;
    sf::Texture tHeroWeapon;
    sf::Texture tHeroShield;

    sf::Sprite sHeroBody;
    sf::Sprite sHeroHead;
    sf::Sprite sHeroWeapon;
    sf::Sprite sHeroShield;

    sf::IntRect spriteRect;
};

#endif //ISORPG_COMP_TEXTURE_H
