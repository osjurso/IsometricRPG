
#ifndef ISORPG_RESOLVEPOSITIONCHANGE_H
#define ISORPG_RESOLVEPOSITIONCHANGE_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <iostream>

#include <components/Comp_position.h>
#include <components/Comp_movable.h>
#include <components/Comp_animation.h>




struct PositionChange
{
public:

    void change(anax::World& world, anax::Entity player);
private:
    void moveCreature(anax::Entity& entity);

};


#endif //ISORPG_RESOLVEPOSITIONCHANGE_H
