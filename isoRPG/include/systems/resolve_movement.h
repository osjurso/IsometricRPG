
#ifndef ISORPG_RESOLVE_MOVMENT_H
#define ISORPG_RESOLVE_MOVMENT_H

#include <states/state_base.h>
#include <iostream>
#include <anax/System.hpp>

#include <components/Comp_size.h>
#include <components/Comp_mousedOver.h>
#include <components/Comp_position.h>

#include <components/Comp_animation.h>
#include <components/Comp_Texture.h>

class ResolveMovement
{
public:
    void resolveMovement(anax::World &world, float deltaTime);

private:
    void Walk(anax::Entity& entity, float deltaTime);

    void Idle(anax::Entity& entity, float deltaTime);

    void Attack(anax::Entity& entity, float deltaTime);

    void Defend(anax::Entity& entity, float deltaTime);

};

#endif //ISORPG_RESOLVE_MOVMENT_H
