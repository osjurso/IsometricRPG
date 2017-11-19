#ifndef ISORPG_DRAWABLE_H
#define ISORPG_DRAWABLE_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_animation.h>


class Draweble
{
public:
    void makeDraweble(sf::Texture& texture,sf::Texture& texture1, sf::Texture& texture2, sf::Texture& texture3,int Left, int Top, anax::Entity& entity, std::string state)
    {
        entity.addComponent<TextureComponent>();
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
        textureComponent.tHeroBody = texture;
        textureComponent.sHeroBody.setTexture(texture);
        textureComponent.tHeroHead = texture1;
        textureComponent.sHeroHead.setTexture(texture1);
        textureComponent.tHeroWeapon = texture2;
        textureComponent.sHeroWeapon.setTexture(texture2);
        textureComponent.tHeroShield = texture3;
        textureComponent.sHeroShield.setTexture(texture3);

        entity.addComponent<PositionComponent>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        positionComponent.YPos = Top;
        positionComponent.XPos = Left;

        entity.addComponent<SizeComponent>();
        SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
        sizeComponent.Height = textureComponent.tHeroBody.getSize().x;
        sizeComponent.Width = textureComponent.tHeroBody.getSize().y;
        sizeComponent.Height = textureComponent.tHeroHead.getSize().x;
        sizeComponent.Width = textureComponent.tHeroHead.getSize().y;
        sizeComponent.Height = textureComponent.tHeroWeapon.getSize().x;
        sizeComponent.Width = textureComponent.tHeroWeapon.getSize().y;
        sizeComponent.Height = textureComponent.tHeroShield.getSize().x;
        sizeComponent.Width = textureComponent.tHeroShield.getSize().y;

        entity.addComponent<StateComponent>();
        StateComponent& stateComponent = entity.getComponent<StateComponent>();
        stateComponent.state = state;
        entity.activate();
    }

    void makeDraweble(sf::Texture& texture,int Left, int Top, anax::Entity& entity, std::string state)
    {

        entity.addComponent<TextureComponent>();
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
        textureComponent.tHeroBody = texture;
        textureComponent.sHeroBody.setTexture(texture);

        entity.addComponent<PositionComponent>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        positionComponent.YPos = Top;
        positionComponent.XPos = Left;

        entity.addComponent<SizeComponent>();
        SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
        sizeComponent.Height = textureComponent.tHeroBody.getSize().x;
        sizeComponent.Width = textureComponent.tHeroBody.getSize().y;

        entity.addComponent<StateComponent>();
        StateComponent& stateComponent = entity.getComponent<StateComponent>();
        stateComponent.state = state;
        entity.activate();
    }
};

#endif //ISORPG_DRAWABLE_H
