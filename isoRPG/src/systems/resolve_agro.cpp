

#include <include/systems/resolve_agro.h>
#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>


#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_moveble.h>

void ResolveAgro::agro(anax::Entity player, anax::World &world)
{
    auto enteties = world.getEntities();
    int range = 50;
    sf::IntRect agroArea;
    PositionComponent playerPos = player.getComponent<PositionComponent>();
    SizeComponent playerSize = player.getComponent<SizeComponent>();
    agroArea.left = playerPos.SpriteLeft - range;
    agroArea.top = playerPos.SpriteTop - range;
    agroArea.height = 2*range + playerSize.SpriteHeight;
    agroArea.width = 2*range + playerSize.SpriteWhith;

    for(auto i : enteties)
    {
        if(i.hasComponent<Movable>() && i.getId() != player.getId())
        {
            PositionComponent positionComponent = i.getComponent<PositionComponent>();
            Movable& movable = i.getComponent<Movable>();
            if(agroArea.contains(positionComponent.SpriteLeft,positionComponent.SpriteTop))
            {
                movable.agro = true;
                std::cout << "Player in agroarea" << std::endl;
            }
        }
    }
}
