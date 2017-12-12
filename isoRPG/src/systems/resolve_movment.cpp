#include <systems/resolve_movment.h>
#include <include/components/Comp_moveble.h>


void ResolveMovment::resolveMovment(anax::World& world, float deltaTime) {

    auto entities = world.getEntities();
    for (auto i : entities) {
        if (i.hasComponent<Movable>()) {
        AnimationComponent& animationComponent = i.getComponent<AnimationComponent>();
        if (animationComponent.animationDirection == 0) {
            if (animationComponent.direction != "East")animationComponent.changedDirection = true;
            animationComponent.direction = "East";
            animationComponent.movementDirection.x += animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.row = animationComponent.rowEast;

        } else if (animationComponent.animationDirection == 1) {
            if (animationComponent.direction != "SouthEast")animationComponent.changedDirection = true;
            animationComponent.direction = "SouthEast";
            animationComponent.movementDirection.x -= animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.movementDirection.y += animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.row = animationComponent.rowSouthEast;

        } else if (animationComponent.animationDirection == 2) {
            if (animationComponent.direction != "South")animationComponent.changedDirection = true;
            animationComponent.direction = "South";
            animationComponent.movementDirection.y += animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.row = animationComponent.rowSouth;

        } else if (animationComponent.animationDirection == 3) {
            if (animationComponent.direction != "SouthWest")animationComponent.changedDirection = true;
            animationComponent.direction = "SouthWest";
            animationComponent.movementDirection.x -= animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.movementDirection.y += animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.row = animationComponent.rowSouthWest;

        } else if (animationComponent.animationDirection == 4) {
            if (animationComponent.direction != "West")animationComponent.changedDirection = true;
            animationComponent.direction = "West";
            animationComponent.movementDirection.x -= animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.row = animationComponent.rowWest;

        } else if (animationComponent.animationDirection == 5) {
            if (animationComponent.direction != "NorthWest")animationComponent.changedDirection = true;
            animationComponent.direction = "NorthWest";
            animationComponent.movementDirection.x -= animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.movementDirection.y -= animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.row = animationComponent.rowNorthWest;

        } else if (animationComponent.animationDirection == 6) {
            if (animationComponent.direction != "North")animationComponent.changedDirection = true;
            animationComponent.direction = "North";
            animationComponent.movementDirection.y -= animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.row = animationComponent.rowNorth;

        } else if (animationComponent.animationDirection == 7) {
            if (animationComponent.direction != "NorthEast")animationComponent.changedDirection = true;
            animationComponent.direction = "NorthEast";
            animationComponent.movementDirection.x += animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.movementDirection.y -= animationComponent.movementSpeed * animationComponent.deltaTime;
            animationComponent.row = animationComponent.rowNorthEast;
        }

            if(animationComponent.action == "Walk")Walk(i,deltaTime);
            if(animationComponent.action == "Idle")Idle(i,deltaTime);
            if(animationComponent.action == "Attack")Attack(i,deltaTime);
            if(animationComponent.action == "Defend")Defend(i,deltaTime);
            if(animationComponent.action == "Die")Die(i,deltaTime);
        }
    }
}

void ResolveMovment::Walk(anax::Entity &entity, float deltaTime)
{
    TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.currentImage.y = animationComponent.row;

    animationComponent.totalTime += deltaTime;

    if(animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime)
    {
        animationComponent.currentImage.x = animationComponent.walkStart;
        animationComponent.changedDirection = false;

    }
    else if(animationComponent.totalTime >= animationComponent.switchTime)
    {
        animationComponent.totalTime -= animationComponent.switchTime;
        animationComponent.currentImage.x++;

        if (animationComponent.currentImage.x >= animationComponent.walkEnd) {
            animationComponent.currentImage.x = animationComponent.walkStart;
        }
    }

    textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
    textureComponent.spriteRect.left = (animationComponent.currentImage.x +1)* abs(textureComponent.spriteRect.width);

}
void ResolveMovment::Idle(anax::Entity &entity, float deltaTime)
{
    TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.currentImage.y = animationComponent.row;
    animationComponent.currentImage.x = animationComponent.idleStart;

    animationComponent.totalTime += deltaTime;

    //animationComponent.changedDirection = false;

    if(animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime)
    {
        animationComponent.currentImage.x = animationComponent.idleStart;
        animationComponent.changedDirection = false;

    }else if(animationComponent.totalTime >= animationComponent.switchTime) {
        animationComponent.totalTime -= animationComponent.switchTime;
        animationComponent.currentImage.x++;

        if (animationComponent.currentImage.x >= animationComponent.idleEnd) {
            animationComponent.currentImage.x = animationComponent.idleStart;
        }
    }

    textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
    textureComponent.spriteRect.left = (animationComponent.currentImage.x +1)* abs(textureComponent.spriteRect.width);

}
void ResolveMovment::Attack(anax::Entity &entity, float deltaTime)
{
    sf::Clock attackClock;
    float attackClockTemp = attackClock.getElapsedTime().asMilliseconds();

    TextureComponent &textureComponent = entity.getComponent<TextureComponent>();
    AnimationComponent &animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.currentImage.y = animationComponent.row;

    animationComponent.totalTime += deltaTime;

        if (animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime) {
            animationComponent.currentImage.x = animationComponent.attackStart;
            animationComponent.changedDirection = false;

        } else if (attackClockTemp <= animationComponent.switchTime) {
            animationComponent.totalTime -= animationComponent.switchTime;
            animationComponent.currentImage.x++;

            if (animationComponent.currentImage.x >= animationComponent.attackEnd) {
                animationComponent.currentImage.x = animationComponent.attackStart;
                attackClock.restart().asMilliseconds();
            }

            textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
            textureComponent.spriteRect.left = (animationComponent.currentImage.x + 1)* abs(textureComponent.spriteRect.width);
        }
    }

void ResolveMovment::Defend(anax::Entity &entity, float deltaTime)
{
    TextureComponent &textureComponent = entity.getComponent<TextureComponent>();
    AnimationComponent &animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.currentImage.y = animationComponent.row;

    animationComponent.totalTime += deltaTime;

        if (animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime) {
            animationComponent.currentImage.x = animationComponent.defendStart;
            animationComponent.changedDirection = false;

        } else if (animationComponent.totalTime >= animationComponent.switchTime) {
            animationComponent.totalTime -= animationComponent.switchTime;
            animationComponent.currentImage.x++;

            if (animationComponent.currentImage.x >= animationComponent.defendEnd) {
                animationComponent.currentImage.x = animationComponent.defendStart;
            }
        }
    textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
    textureComponent.spriteRect.left = (animationComponent.currentImage.x + 1)* abs(textureComponent.spriteRect.width);
}

void ResolveMovment::Die(anax::Entity &entity, float deltaTime) {
    TextureComponent &textureComponent = entity.getComponent<TextureComponent>();
    AnimationComponent &animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.currentImage.y = animationComponent.row;

    animationComponent.totalTime += deltaTime;

    std::cout << "Die method" << std::endl;

    if (animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime) {
        animationComponent.currentImage.x = animationComponent.dieStart;
        animationComponent.changedDirection = false;

    } else if (animationComponent.totalTime >= animationComponent.switchTime) {
        animationComponent.totalTime -= animationComponent.switchTime;
        animationComponent.currentImage.x++;

        if (animationComponent.currentImage.x >= animationComponent.dieEnd) {
            animationComponent.currentImage.x = animationComponent.dieStart;
        }
    }
    textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
    textureComponent.spriteRect.left = (animationComponent.currentImage.x + 1)* abs(textureComponent.spriteRect.width);
}

