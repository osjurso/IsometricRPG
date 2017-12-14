#include <systems/resolvePositionChange.h>
#include <string>

void PositionChange::change(anax::World &world, anax::Entity player)
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

void PositionChange::moveCreature(anax::Entity &entity)
{/*


    Movable& moveble = entity.getComponent<Movable>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    if(moveble.path != "" && moveble.current <= moveble.path.length())
    {
        int nr = 0;
        for(int i = moveble.current; i< moveble.speed+ moveble.current; i++)
        {
            positionComponent.XPos += moveble.moveX[i];
            positionComponent.YPos += moveble.moveY[i];
            positionComponent.SpriteLeft += moveble.moveX[i];
            positionComponent.SpriteTop += moveble.moveY[i];



            int tempInt = moveble.path.at(i);
            tempInt = tempInt-48;
            animationComponent.animationDirection = tempInt;
            nr++;

            if(moveble.path.length() == i+1) continue;
        }
        moveble.current += nr;
    }
    */
    Movable& moveble = entity.getComponent<Movable>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();



}