

#include <systems/resolvePositionChange.h>


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
    int speed = 10;
    if(moveble.path.at(0) == '0')
    {
        //Move East
        animationComponent.direction = "Right";
        positionComponent.XPos += speed;
        positionComponent.SpriteLeft += speed;
        animationComponent.animationDirection = 0;

    }else if(moveble.path.at(0) == '1')
    {
        //Move South East
        positionComponent.YPos += speed/2;
        positionComponent.SpriteTop += speed/2;
        positionComponent.XPos += speed/2;
        positionComponent.SpriteLeft += speed/2;
        animationComponent.animationDirection = 1;

    }else if(moveble.path.at(0) == '2')
    {
        //Move South
        animationComponent.direction = "Down";
        positionComponent.YPos += speed;
        positionComponent.SpriteTop += speed;
        animationComponent.animationDirection = 2;

    }else if(moveble.path.at(0) == '3')
    {
        //Move South West
        positionComponent.YPos += speed/2;
        positionComponent.SpriteTop += speed/2;
        positionComponent.XPos -= speed/2;
        positionComponent.SpriteLeft -= speed/2;
        animationComponent.animationDirection = 3;

    }else if(moveble.path.at(0) == '4')
    {
        //Move West
        animationComponent.direction = "Left";
        positionComponent.XPos -= speed;
        positionComponent.SpriteLeft -= speed;
        animationComponent.animationDirection = 4;

    }
    else if(moveble.path.at(0) == '5')
    {
        //Move North West
        positionComponent.YPos -= speed/2;
        positionComponent.SpriteTop -= speed/2;
        positionComponent.XPos -= speed/2;
        positionComponent.SpriteLeft -= speed/2;
        animationComponent.animationDirection = 5;

    }else if(moveble.path.at(0) == '6')
    {
        //Move North
        animationComponent.direction = "Up";
        positionComponent.YPos -= speed;
        positionComponent.SpriteTop -= speed;
        animationComponent.animationDirection = 6;

    }else if(moveble.path.at(0) == '7')
    {
        //Move South West
        positionComponent.YPos -= speed/2;
        positionComponent.SpriteTop -= speed/2;
        positionComponent.XPos += speed/2;
        positionComponent.SpriteLeft += speed/2;
        animationComponent.animationDirection = 7;

    }
    //std::cout << "Entity ID: "<< entity.getId() << "  Path: " <<  moveble.path << std::endl;
    moveble.path.erase(0,1);
}