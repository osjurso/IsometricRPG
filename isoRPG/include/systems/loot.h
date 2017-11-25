//
// Created by Bjornar on 11/16/2017.
//

#ifndef ISORPG_LOOT_H
#define ISORPG_LOOT_H

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


class Loot
{
public:
    void loot( anax::World& world, anax::Entity target, anax::Entity picker)
    {
        if(target.getId() != picker.getId())
        {
            PositionComponent& positionComponent = target.getComponent<PositionComponent>();
            SizeComponent& sizeComponent = target.getComponent<SizeComponent>();
            Looteble& looteble = target.getComponent<Looteble>();

            PositionComponent& Pickerposition = picker.getComponent<PositionComponent>();
            SizeComponent& Pickersize = picker.getComponent<SizeComponent>();
            Looteble& pickerLoot = picker.getComponent<Looteble>();

            int pickupraduis =50;

            sf::IntRect picker;
            picker.top = Pickerposition.YPos -pickupraduis;
            picker.left = Pickerposition.XPos -pickupraduis;
            picker.height = 2*pickupraduis;
            picker.width = 2*pickupraduis;


            if(picker.contains(positionComponent.XPos, positionComponent.YPos))
            {
                std::cout<< "Player looted " << looteble.gold << " gold from "<< target.getId() << " that was whithin " << pickupraduis  << " of the player " << std::endl;
                pickerLoot.gold += looteble.gold;
                looteble.gold = 0;
            }
        }
    }
};


#endif //ISORPG_LOOT_H
