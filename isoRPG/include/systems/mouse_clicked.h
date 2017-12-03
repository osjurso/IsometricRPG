
#ifndef ISORPG_MOUSE_CLICKED_H
#define ISORPG_MOUSE_CLICKED_H

#include <anax/System.hpp>
#include <states/state_base.h>


#include <components/Comp_size.h>
#include <components/Comp_mousedOver.h>
#include <components/Comp_position.h>
#include <iostream>
#include "loot.h"
#include "talk.h"
#include <include/systems/pathfinding.h>
#include <components/Comp_moveble.h>

struct MouseClicked : anax::System<anax::Requires<PositionComponent, SizeComponent, MousedOver>>
{
public:
    MouseClicked(StateBase::Context context);
    void Clicked(anax::Entity& player,sf::View cam, float zoom);
private:
    void process(anax::Entity& e, float MouseXT, float MouseYT, anax::World& world, anax::Entity player, sf::RenderWindow& window, sf::View cam, float zoom);
    void createPlayerPath(anax::Entity player, float MouseX, float MouseY);

    StateBase::Context context;
};

#endif //ISORPG_MOUSE_CLICKED_H
