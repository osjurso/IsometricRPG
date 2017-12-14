
#ifndef ISORPG_UPDATEMENU_H
#define ISORPG_UPDATEMENU_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <iostream>

#include <components/Comp_position.h>
#include <components/Comp_movable.h>
#include <components/Comp_animation.h>




struct UpdateMenu
{
public:

    void change(anax::World& world, anax::Entity player, sf::RenderWindow& window);
private:

};

#endif //ISORPG_UPDATEMENU_H
