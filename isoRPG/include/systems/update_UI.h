
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
#include <include/components/Comp_Changeble.h>
#include <include/components/Comp_ActionTimers.h>


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
                if(i.hasComponent<ChangebleComponent>())
                {
                    if(i.hasComponent<SqureComponent>())
                    {
                        sf::Vector2f size;
                        size.x = i.getComponent<SizeComponent>().Whith*(player.getComponent<HealthComponent>().health/player.getComponent<HealthComponent>().maxHealth);
                        size.y = i.getComponent<SqureComponent>().rectShape.getSize().y;
                        i.getComponent<SqureComponent>().rectShape.setSize(size);
                    }else if(i.getComponent<ChangebleComponent>().source == "Attack")
                    {
                        float size = player.getComponent<ActionTimer>().AttackTimer.getElapsedTime().asSeconds()/player.getComponent<ActionTimer>().AttackCooldown;
                        if(0.25*size >0.25) size = 1;
                        i.getComponent<TextureComponent>().sprite[0].setScale(0.25*size,0.25);
                    }else if(i.getComponent<ChangebleComponent>().source == "Defend")
                    {
                        float size = 0;
                        if(player.getComponent<AnimationComponent>().action == "Defend")
                        {
                            size = 1;
                        }
                        i.getComponent<TextureComponent>().sprite[0].setScale(0.25*size,0.25);
                    }else if(i.getComponent<ChangebleComponent>().source == "Potion")
                    {
                        float size = player.getComponent<ActionTimer>().PotionTimer.getElapsedTime().asSeconds()/player.getComponent<ActionTimer>().PotionCooldown;
                        if(0.25*size >0.25) size = 1;
                        i.getComponent<TextureComponent>().sprite[0].setScale(0.25*size,0.25);
                    }

                }
            }
        }
    }
};

#endif //ISORPG_UPDATE_UI_H
