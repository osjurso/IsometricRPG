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
                animationComponent.currentImage.x = 4;
                animationComponent.changedDirection = false;

            }
            else if(animationComponent.totalTime >= animationComponent.switchTime)
            {
                animationComponent.totalTime -= animationComponent.switchTime;
                animationComponent.currentImage.x++;


                if (animationComponent.currentImage.x >= 11) {
                    animationComponent.currentImage.x = 3;
                }
        }

        textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
        textureComponent.spriteRect.left = (animationComponent.currentImage.x +1)* abs(textureComponent.spriteRect.width);

    }
    void Idle(anax::Entity& entity, float deltaTime)
    {
        bool isMoving = false;

    }
    void Attack(anax::Entity& entity, float deltaTime)
    {

    }
    void Defend(anax::Entity& entity, float deltaTime)
    {

    }
};

#endif //ISORPG_RESOLVE_MOVMENT_H
