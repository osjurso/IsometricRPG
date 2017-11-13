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

void resolveMovment(anax::Entity& entity, std::string Occurrence)
{

    if(Occurrence == "Walk")Walk(entity);
    if(Occurrence == "Idle")Idle(entity);
    if(Occurrence == "Attack")Attack(entity);
    if(Occurrence == "Defend")Defend(entity);


}

    void Walk(anax::Entity& entity)
    {
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();

        AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
        animationComponent.currentImage.y = animationComponent.row;

        std::string temp = animationComponent.direction;

        if(animationComponent.direction == "Up")
        {
            animationComponent.totalTime += animationComponent.deltaTime;
            if(animationComponent.changedDirection)
            {
                animationComponent.currentImage.x = 4;
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

    }
    void Idle(anax::Entity& entity)
    {
        bool isMoving = false;

    }
    void Attack(anax::Entity& entity)
    {

    }
    void Defend(anax::Entity& entity)
    {

    }
};

#endif //ISORPG_RESOLVE_MOVMENT_H
