#ifndef ISORPG_ATTACK_H
#define ISORPG_ATTACK_H

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


class Attack : anax::System<anax::Requires<PositionComponent, SizeComponent>>
{
public:
    Attack(){}

    void resolveAttack( anax::World& world, anax::Entity attacker)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            if(i.getId() == attacker.getId())
            {
                if(i.hasComponent<HealthComponent>())
                {
                    HealthComponent& healthComponent = i.getComponent<HealthComponent>();


                    PositionComponent& positionComponent = i.getComponent<PositionComponent>();
                    SizeComponent& sizeComponent = i.getComponent<SizeComponent>();

                    PositionComponent& Attackerposition = attacker.getComponent<PositionComponent>();
                    SizeComponent& Attackersize = attacker.getComponent<SizeComponent>();
                    float attackerX = Attackerposition.XPos + (Attackersize.Width/2);
                    float attackerY = Attackerposition.YPos + (Attackersize.Height/2);

                    bool Left = false;
                    bool Right = false;
                    bool Bottom = false;
                    bool Top = false;
                    int attackradius = 200;

                    if(attackerX + attackradius >= positionComponent.XPos)
                        Left = true;

                    if(attackerX + attackradius <= positionComponent.XPos+ sizeComponent.Height)
                        Right = true;

                    if(attackerY + attackradius >= positionComponent.YPos)
                        Top = true;

                    if(attackerY + attackradius <= positionComponent.YPos + sizeComponent.Width)
                        Bottom = true;


                    if(Left && Right && Top && Bottom)
                    {
                        std::cout<< "enemy inside radius of" << attackradius << std::endl;
                        healthComponent.health - 10;//TODO: change to weapons damage (attacker.weapondamage)
                    }


                }
            }

        }
    }
};

#endif //ISORPG_ATTACK_H
