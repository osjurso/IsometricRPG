#include <include/components/Comp_mousedOver.h>
#include"systems/updateMenu.h"

void UpdateMenu::change(anax::World &world, anax::Entity player, sf::RenderWindow& window)
{
    auto entitys = world.getEntities();
    for(auto i: entitys)
    {
        window.getSize().x;
        if(i.hasComponent<MousedOver>())
        {
            //i.getComponent<PositionComponent>().XPos = i.getComponent<PositionComponent>().XPos
        }
    }
}
