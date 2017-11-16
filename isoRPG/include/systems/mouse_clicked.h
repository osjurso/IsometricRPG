
#ifndef ISORPG_MOUSE_CLICKED_H
#define ISORPG_MOUSE_CLICKED_H

#include <anax/System.hpp>
#include <states/state_base.h>


#include <include/components/Comp_size.h>
#include <include/components/Comp_mousedOver.h>
#include <components/Comp_position.h>
#include <iostream>
#include <include/components/Comp_looteble.h>
#include "loot.h"

struct MouseClicked : anax::System<anax::Requires<PositionComponent, SizeComponent, MousedOver>>
{
public:
    MouseClicked()
    {}
    void Clicked(anax::World& world, float MouseX, float MouseY , anax::Entity& entity)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            if(i.hasComponent<MousedOver>())
                process(i,MouseX,MouseY, world, entity);
        }
    }


private:
    void process(anax::Entity& e, float MouseX, float MouseY, anax::World& world, anax::Entity player)
    {
        PositionComponent& positionComponent = e.getComponent<PositionComponent>();
        SizeComponent& sizeComponent = e.getComponent<SizeComponent>();
        //MousedOver& mousedOver = e.getComponent<MousedOver>();

        bool Venstre = false;
        bool Hoyre = false;
        bool Nede = false;
        bool Oppe = false;

        if(MouseX >= positionComponent.XPos)
            Venstre = true;

        if(MouseX <= positionComponent.XPos+ sizeComponent.Height)
            Hoyre = true;

        if(MouseY >= positionComponent.YPos)
            Oppe = true;

        if(MouseY <= positionComponent.YPos + sizeComponent.Whith)
            Nede = true;


        if(Venstre && Hoyre && Oppe && Nede)
        {
            std::cout<< "You Pressed a element" << std::endl;
            //TODO implement functions to run when element is pressed
            std::cout<< "You Pressed: " << e.getId() << std::endl;
            if(e.hasComponent<Looteble>())
            {
                Loot loot;
                loot.loot(world,e, player);
            }

        }
    }
};

#endif //ISORPG_MOUSE_CLICKED_H
