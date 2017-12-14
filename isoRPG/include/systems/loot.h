#ifndef ISORPG_LOOT_H
#define ISORPG_LOOT_H

#include <iostream>

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <states/state_base.h>
#include <application.h>

#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_healt.h>
#include <components/Comp_lootable.h>


class Loot
{
public:
    void loot( anax::World& world, anax::Entity target, anax::Entity picker)
    {
        if(target.getId() != picker.getId())
        {
            PositionComponent& positionComponent = target.getComponent<PositionComponent>();
            SizeComponent& sizeComponent = target.getComponent<SizeComponent>();
            Lootable& lootable = target.getComponent<Lootable>();

            PositionComponent& Pickerposition = picker.getComponent<PositionComponent>();
            SizeComponent& Pickersize = picker.getComponent<SizeComponent>();
            Lootable& pickerLoot = picker.getComponent<Lootable>();

            int pickupraduis =50;

            sf::IntRect picker;
            picker.top = Pickerposition.YPos -pickupraduis;
            picker.left = Pickerposition.XPos -pickupraduis;
            picker.height = 2*pickupraduis;
            picker.width = 2*pickupraduis;


            if(picker.contains(positionComponent.SpriteLeft, positionComponent.SpriteTop))
            {
                std::cout<< "Player looted " << lootable.gold << " gold from "<< target.getId() << " that was whithin " << pickupraduis  << " of the player " << std::endl;
                pickerLoot.gold += lootable.gold;
                lootable.gold = 0;
            }
        }
    }
};


#endif //ISORPG_LOOT_H
