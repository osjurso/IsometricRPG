

#include <systems/resolvePositionChange.h>
#include <string>

void PostitonChange::change(anax::World &world, anax::Entity player)
{
    auto enteties = world.getEntities();
    for(auto i : enteties)
    {
        if(i.hasComponent<Movable>())
        {
            if(i.getComponent<Movable>().path != "")
            {
            moveCreature(i);
            }else
            {
                i.getComponent<Movable>().agro = false;
            }
        }
    }
}

void PostitonChange::moveCreature(anax::Entity &entity)
{
    Movable& moveble = entity.getComponent<Movable>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    if(moveble.path != "")
    {
        for(int i = moveble.curent; i< moveble.speed+ moveble.curent; i++)
        {
            positionComponent.XPos += moveble.moveX[i];
            positionComponent.YPos += moveble.moveY[i];
            positionComponent.SpriteLeft += moveble.moveX[i];
            positionComponent.SpriteTop += moveble.moveY[i];
            int tempInt = moveble.path.at(i);
            tempInt = tempInt-48;
            animationComponent.animationDirection = tempInt;

            if(moveble.path.length() == i+1) i = moveble.speed;


        }
    }
}