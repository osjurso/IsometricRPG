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


class Attack
{
public:
    Attack(){}

    void resolveAttack( anax::World& world, anax::Entity attacker)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            if(i.hasComponent<HealthComponent>())
            {
                if(i.getId() != attacker.getId())
                {

                    HealthComponent& healthComponent = i.getComponent<HealthComponent>();
                    PositionComponent& positionComponent = i.getComponent<PositionComponent>();
                    SizeComponent& sizeComponent = i.getComponent<SizeComponent>();
                    Looteble& looteble = i.getComponent<Looteble>();

                    PositionComponent& Attackerposition = attacker.getComponent<PositionComponent>();
                    SizeComponent& Attackersize = attacker.getComponent<SizeComponent>();
                    Looteble& attackerLoot = attacker.getComponent<Looteble>();
                    float attackerX = Attackerposition.XPos + (Attackersize.Whith/2);
                    float attackerY = Attackerposition.YPos + (Attackersize.Height/2);
                    int attackradius = 200;

                    sf::IntRect attacker;
                    attacker.top = Attackerposition.YPos -attackradius;
                    attacker.left = Attackerposition.XPos -attackradius;
                    attacker.height = 2*attackradius;
                    attacker.width = 2*attackradius;

                    if(attacker.contains(positionComponent.XPos, positionComponent.YPos))
                    {
                        std::cout<< "enemy inside radius of " << attackradius << std::endl;
                        healthComponent.health -= 5;//TODO: change to weapons damage (attacker.weapondamage)
                        std::cout<< healthComponent.health << std::endl;
                    }
                    if(healthComponent.health <= 0)
                    {
                        attackerLoot.gold += looteble.gold;
                        i.kill();
                        world.refresh();
                    }


                }
            }

        }
    }
};

#endif //ISORPG_ATTACK_H
