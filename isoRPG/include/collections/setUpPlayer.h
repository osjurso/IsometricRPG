
#ifndef ISORPG_SETUPPLAYER_H
#define ISORPG_SETUPPLAYER_H

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
#include <include/components/Comp_moveble.h>


class SetUpPlayer
{
public:
    void setUpPlayer(anax::Entity& entity, sf::Texture& texture,sf::Texture& texture1, sf::Texture& texture2, sf::Texture& texture3 ,sf::RenderWindow& window)
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
        textureComponent.spriteRect.height = 128;
        textureComponent.spriteRect.width = 128;


        entity.addComponent<PositionComponent>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        positionComponent.YPos = 0;
        positionComponent.XPos = 0;

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

        entity.addComponent<AnimationComponent>();
        AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
        animationComponent.imageCounter.x = 32;
        animationComponent.imageCounter.y = 8;
        animationComponent.switchTime = 0.2f;
        animationComponent.pixels = 128;
        animationComponent.movementSpeed = 20;
        animationComponent.row =0;
        animationComponent.currentImage.x =0;
        //animationComponent.animationClock.restart().asSeconds();

        entity.addComponent<StateComponent>();
        StateComponent& stateComponent = entity.getComponent<StateComponent>();
        stateComponent.state = "Game";

        entity.addComponent<Moveble>();
        Moveble& moveble = entity.getComponent<Moveble>();
        moveble.speed = 5;

        entity.activate();
    }
};

#endif //ISORPG_SETUPPLAYER_H
