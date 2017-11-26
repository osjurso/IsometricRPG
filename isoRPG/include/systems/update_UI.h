
#ifndef ISORPG_UPDATE_UI_H
#define ISORPG_UPDATE_UI_H


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
#include <include/components/Comp_UI.h>


class UpdateUI
{
public:
    void update( anax::World& world, sf::View& cam, anax::Entity& player)
    {
        auto enteties = world.getEntities();

        for(auto i : enteties)
        {
            if(i.hasComponent<UIComp>())
            {
                PositionComponent& positionComponent = i.getComponent<PositionComponent>();
                positionComponent.XPos = cam.getCenter().x - (cam.getSize().x/2) + i.getComponent<UIComp>().Xofset;
                positionComponent.YPos = cam.getCenter().y + (cam.getSize().y/2) + i.getComponent<UIComp>().Yofset;

                if(i.hasComponent<TextComponent>())
                {
                    TextComponent& textComponent = i.getComponent<TextComponent>();
                    if(textComponent.content == "Potion")
                    {
                        textComponent.text.setString("x " + std::to_string(player.getComponent<Looteble>().HealtPotion));
                    }

                    if(textComponent.content == "Gold")
                    {
                        textComponent.text.setString("x " + std::to_string(player.getComponent<Looteble>().gold));
                    }
                    if(textComponent.content == "Armor")
                    {
                        textComponent.text.setString("10 + " + std::to_string(player.getComponent<Looteble>().armorModifier));
                    }
                    if(textComponent.content == "Weapon")
                    {
                        textComponent.text.setString("10 + " + std::to_string(player.getComponent<Looteble>().weaponModifier));
                    }

                }
            }
        }
    }
};

#endif //ISORPG_UPDATE_UI_H
