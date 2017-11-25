

#include <include/systems/resolve_agro.h>


void ResolveAgro::agro(anax::Entity player, anax::World &world)
{
    auto enteties = world.getEntities();
    int range = 200;
    sf::IntRect agroArea;
    PositionComponent playerPos = player.getComponent<PositionComponent>();
    SizeComponent playerSize = player.getComponent<SizeComponent>();
    agroArea.left = playerPos.SpriteLeft - range;
    agroArea.top = playerPos.SpriteTop - range;
    agroArea.height = 2*range + playerSize.Height;
    agroArea.width = 2*range + playerSize.Whith;

    for(auto i : enteties)
    {
        if(i.hasComponent<Movable>() && i.getId() != player.getId())
        {
            PositionComponent positionComponent = i.getComponent<PositionComponent>();
            Movable& movable = i.getComponent<Movable>();
            if(agroArea.contains(positionComponent.SpriteLeft,positionComponent.SpriteTop))
            {
                movable.agro = true;
            }
        }
    }
}
