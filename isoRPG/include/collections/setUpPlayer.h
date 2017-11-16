
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
#include <include/components/Comp_healt.h>
#include <include/components/Comp_looteble.h>


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
        positionComponent.YPos = 0;
        positionComponent.XPos = 0;

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
        animationComponent.movementSpeed = 20;
        animationComponent.row =0;
        animationComponent.currentImage.x =0;
        animationComponent.animationClock.restart().asSeconds();

        entity.addComponent<StateComponent>();
        StateComponent& stateComponent = entity.getComponent<StateComponent>();
        stateComponent.state = "Game";

        entity.addComponent<Moveble>();
        Moveble& moveble = entity.getComponent<Moveble>();
        moveble.speed = 5;

        entity.addComponent< Looteble>();
        Looteble& looteble = entity.getComponent<Looteble>();
        looteble.gold =0;

        entity.activate();
    }
    void setUpEnemie(anax::Entity& entity, sf::Texture& texture, sf::RenderWindow& window, int Xpos, int Ypos, std::string diffeculty)
    {
        entity.addComponent<TextureComponent>();
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
        textureComponent.texture = texture;
        textureComponent.sprite.setTexture(texture);
        textureComponent.spriteRect.height = 128;
        textureComponent.spriteRect.width = 128;
        sf::Color red(255,100,100);
        sf::Color blue(100,100,255);


        entity.addComponent<PositionComponent>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        positionComponent.YPos = Xpos;
        positionComponent.XPos = Ypos;

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
        animationComponent.movementSpeed = 20;
        animationComponent.row =0;
        animationComponent.currentImage.x =0;
        animationComponent.animationClock.restart().asSeconds();
        animationComponent.idle = true;

        entity.addComponent<StateComponent>();
        StateComponent& stateComponent = entity.getComponent<StateComponent>();
        stateComponent.state = "Game";

        entity.addComponent<Moveble>();
        Moveble& moveble = entity.getComponent<Moveble>();


        entity.addComponent<HealthComponent>();
        HealthComponent& healthComponent = entity.getComponent<HealthComponent>();

        entity.addComponent< Looteble>();
        Looteble& looteble = entity.getComponent<Looteble>();

        entity.addComponent<MousedOver>();


        if(diffeculty == "Hard")
        {
            textureComponent.sprite.setColor(red);
            healthComponent.maxHealth = 100;
            moveble.speed = 10;
            looteble.gold =50 + (10*rand()%10+1);
        }else if(diffeculty == "Medium")
        {
            textureComponent.sprite.setColor((blue));
            healthComponent.maxHealth = 50;
            moveble.speed = 5;
            looteble.gold =25+(5*rand()%10+1);
        }else
        {
            healthComponent.maxHealth = 20;
            looteble.gold = rand()%10+1;
            moveble.speed = 3;
        }
        healthComponent.health = healthComponent.maxHealth;


        entity.activate();
    }
};

#endif //ISORPG_SETUPPLAYER_H
