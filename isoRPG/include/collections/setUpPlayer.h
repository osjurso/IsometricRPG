
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


class SetUpPlayer
{
public:
    void setUpPlayer(anax::Entity& entity, sf::Texture& texture, sf::RenderWindow& window)
    {
        entity.addComponent<TextureComponent>();
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
        textureComponent.texture = texture;
        textureComponent.sprite.setTexture(texture);
        textureComponent.spriteRect.height = 128;
        textureComponent.spriteRect.width = 128;

        entity.addComponent<PositionComponent>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        positionComponent.YPos = window.getSize().x/2;
        positionComponent.XPos = window.getSize().y/2;

        entity.addComponent<SizeComponent>();
        SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
        sizeComponent.Height = textureComponent.texture.getSize().x;
        sizeComponent.Whith = textureComponent.texture.getSize().y;

        entity.addComponent<AnimationComponent>();
        AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
        animationComponent.imageCounter.x = 32;
        animationComponent.imageCounter.y = 8;
        animationComponent.switchTime = 0.2f;
        animationComponent.pixels = 128;
        animationComponent.movementSpeed = 50;

        entity.activate();
    }
};

#endif //ISORPG_SETUPPLAYER_H
