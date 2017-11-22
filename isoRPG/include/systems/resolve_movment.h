//
// Created by Bjornar on 13.11.2017.
//

#ifndef ISORPG_RESOLVE_MOVMENT_H
#define ISORPG_RESOLVE_MOVMENT_H


#include <anax/System.hpp>
#include <states/state_base.h>


#include <include/components/Comp_size.h>
#include <include/components/Comp_mousedOver.h>
#include <components/Comp_position.h>
#include <iostream>
#include <include/components/Comp_animation.h>
#include <include/components/Comp_Texture.h>


class ResolveMovment
{
public:
ResolveMovment()
{

}

void resolveMovment(anax::Entity& entity, std::string Occurrence, float deltaTime)
{

    if(Occurrence == "Walk")Walk(entity, deltaTime);
    if(Occurrence == "Idle")Idle(entity, deltaTime);
    if(Occurrence == "Attack")Attack(entity, deltaTime);
    if(Occurrence == "Defend")Defend(entity, deltaTime);


}

    void Walk(anax::Entity& entity, float deltaTime)
    {
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
        AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
        animationComponent.currentImage.y = animationComponent.row;
        animationComponent.totalTime += deltaTime;
            if(animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime)
            {
                animationComponent.currentImage.x = animationComponent.walkStart;
                animationComponent.changedDirection = false;

            }
            else if(animationComponent.totalTime >= animationComponent.switchTime)
            {
                animationComponent.totalTime -= animationComponent.switchTime;
                animationComponent.currentImage.x++;

                if (animationComponent.currentImage.x >= animationComponent.walkEnd) {
                    animationComponent.currentImage.x = animationComponent.walkStart;
                }
        }

        textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
        textureComponent.spriteRect.left = (animationComponent.currentImage.x +1)* abs(textureComponent.spriteRect.width);

    }
    void Idle(anax::Entity& entity, float deltaTime)
    {
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
        AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
        animationComponent.currentImage.y = animationComponent.row;
        animationComponent.currentImage.x = animationComponent.idleStart;

        animationComponent.totalTime += deltaTime;

        //animationComponent.changedDirection = false;

        if(animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime)
        {
            animationComponent.currentImage.x = animationComponent.idleStart;
            animationComponent.changedDirection = false;

        }else if(animationComponent.totalTime >= animationComponent.switchTime) {
            animationComponent.totalTime -= animationComponent.switchTime;
            animationComponent.currentImage.x++;

            if (animationComponent.currentImage.x >= animationComponent.idleEnd) {
                animationComponent.currentImage.x = animationComponent.idleEnd;
            }
        }

        textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
        textureComponent.spriteRect.left = (animationComponent.currentImage.x +1)* abs(textureComponent.spriteRect.width);

    }
    void Attack(anax::Entity& entity, float deltaTime) {
        bool attack = true;
        TextureComponent &textureComponent = entity.getComponent<TextureComponent>();
        AnimationComponent &animationComponent = entity.getComponent<AnimationComponent>();
        animationComponent.currentImage.y = animationComponent.row;

        while (attack) {

            animationComponent.totalTime += deltaTime;

            if (animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime) {
                animationComponent.currentImage.x = animationComponent.attackStart;
                animationComponent.changedDirection = false;

            } else if (animationComponent.totalTime >= animationComponent.switchTime) {
                animationComponent.totalTime -= animationComponent.switchTime;
                animationComponent.currentImage.x++;

                if (animationComponent.currentImage.x >= animationComponent.attackEnd) {
                    animationComponent.currentImage.x = animationComponent.attackStart;
                    attack = false;
                }
                textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
                textureComponent.spriteRect.left = (animationComponent.currentImage.x + 1)* abs(textureComponent.spriteRect.width);
            }

        }
    }

    void Defend(anax::Entity& entity, float deltaTime) {
        bool defend = true;
        TextureComponent &textureComponent = entity.getComponent<TextureComponent>();
        AnimationComponent &animationComponent = entity.getComponent<AnimationComponent>();
        animationComponent.currentImage.y = animationComponent.row;

        while (defend) {
            textureComponent.spriteRect.left = (animationComponent.currentImage.x + 1)* abs(textureComponent.spriteRect.width);

            animationComponent.totalTime += deltaTime;

            if (animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime) {
                animationComponent.currentImage.x = animationComponent.defendStart;
                animationComponent.changedDirection = false;

            } else if (animationComponent.totalTime >= animationComponent.switchTime) {
                animationComponent.totalTime -= animationComponent.switchTime;
                animationComponent.currentImage.x++;

                if (animationComponent.currentImage.x >= animationComponent.defendEnd) {
                    animationComponent.currentImage.x = animationComponent.defendStart;
                    defend = false;
                }
            }
        }
        textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
    }
};

#endif //ISORPG_RESOLVE_MOVMENT_H
