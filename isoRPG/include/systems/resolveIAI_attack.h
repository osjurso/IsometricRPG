
#ifndef ISORPG_RESOLVEIAI_ATTACK_H
#define ISORPG_RESOLVEIAI_ATTACK_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_healt.h>
#include <iostream>
#include <include/components/Comp_looteble.h>
#include <include/components/Comp_ActionTimers.h>


class ResolveAIAttack
{
public:
    void resolve( anax::World& world, anax::Entity& player)
    {
        auto entitys = world.getEntities();
        for(auto i : entitys)
        {
            if(i.hasComponent<ActionTimer>() && i.getId() != player.getId())
            {
                if(i.getComponent<ActionTimer>().AttackTimer.getElapsedTime().asSeconds() > i.getComponent<ActionTimer>().AttackCooldown)
                {
                    float playerCenterX = player.getComponent<PositionComponent>().SpriteLeft;
                    float playerCenterY = player.getComponent<PositionComponent>().SpriteTop;

                    float iCenterX  = i.getComponent<PositionComponent>().SpriteLeft ;
                    float iCenterY  = i.getComponent<PositionComponent>().SpriteTop ;

                    float distanceX = playerCenterX -iCenterX;
                    if(distanceX < 0) distanceX = distanceX*-1;

                    float distanceY = playerCenterY -iCenterY;
                    if(distanceY < 0) distanceY = distanceY*-1;

                    if(distanceX + distanceY < 50)
                    {
                        player.getComponent<HealthComponent>().health -=  (i.getComponent<Looteble>().weapon - (player.getComponent<Looteble>().armor + player.getComponent<Looteble>().armorModifier));
                    }
                    i.getComponent<ActionTimer>().AttackTimer.restart().asSeconds();

                }
            }
        }
    }
};

#endif //ISORPG_RESOLVEIAI_ATTACK_H
