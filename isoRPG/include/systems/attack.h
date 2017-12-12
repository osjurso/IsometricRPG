#ifndef ISORPG_ATTACK_H
#define ISORPG_ATTACK_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_healt.h>
#include <iostream>
#include <components/Comp_looteble.h>
#include <include/components/Comp_Dying.h>


class Attack
{
public:
    void resolveAttack( anax::World& world, anax::Entity& entity)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            if(i.hasComponent<HealthComponent>())
            {
                if(i.getId() !=  entity.getId())
                {

                    HealthComponent& healthComponent = i.getComponent<HealthComponent>();
                    PositionComponent& positionComponent = i.getComponent<PositionComponent>();
                    SizeComponent& sizeComponent = i.getComponent<SizeComponent>();
                    Looteble& looteble = i.getComponent<Looteble>();

                    PositionComponent& Attackerposition =  entity.getComponent<PositionComponent>();
                    SizeComponent& Attackersize = entity.getComponent<SizeComponent>();
                    Looteble& attackerLoot =  entity.getComponent<Looteble>();
                    float attackerX = Attackerposition.XPos + (Attackersize.Whith/2);
                    float attackerY = Attackerposition.YPos + (Attackersize.Height/2);
                    int attackradius = 50;

                    sf::IntRect attacker;
                    attacker.top = Attackerposition.YPos -attackradius;
                    attacker.left = Attackerposition.XPos -attackradius;
                    attacker.height = 2*attackradius;
                    attacker.width = 2*attackradius;

                    if(attacker.contains(positionComponent.XPos, positionComponent.YPos))
                    {
                        healthComponent.health -= entity.getComponent<Looteble>().weapon + entity.getComponent<Looteble>().weaponModifier;
                    }
                    if(healthComponent.health <= 0)
                    {
                        attackerLoot.gold += looteble.gold;
                        i.addComponent<DyingComponent>();
                        i.getComponent<DyingComponent>().dying = true;
                        entity.getComponent<HealthComponent>().totalKills +=1;
                        entity.getComponent<HealthComponent>().unpaidKills +=1;
                    }


                }
            }

        }
    }
};

#endif //ISORPG_ATTACK_H
