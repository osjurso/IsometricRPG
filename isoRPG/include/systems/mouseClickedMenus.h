
#ifndef ISORPG_MOUSECLICKEDMENUS_H
#define ISORPG_MOUSECLICKEDMENUS_H

#include <anax/System.hpp>
#include <states/state_base.h>


#include <components/Comp_size.h>
#include <components/Comp_mousedOver.h>
#include <components/Comp_position.h>
#include <iostream>
#include <include/systems/pathfinding.h>
#include <components/Comp_movable.h>
#include <components/Comp_AssosiateFunc.h>

class mouseClickedMenus : anax::System<anax::Requires<PositionComponent, SizeComponent, MousedOver>>
{
public:
    mouseClickedMenus(StateBase::Context context);
    void Clicked();
private:
    void process(anax::Entity& e, float MouseX, float MouseY,  sf::RenderWindow& window);

    StateBase::Context context;
};


#endif //ISORPG_MOUSECLICKEDMENUS_H
