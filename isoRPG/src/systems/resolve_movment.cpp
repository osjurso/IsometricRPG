#include <systems/resolve_movment.h>



void ResolveMovment::resolveMovment(anax::Entity &entity, std::string Occurrence, float deltaTime)
{

    if(Occurrence == "Walk")Walk(entity, deltaTime);
    if(Occurrence == "Idle")Idle(entity, deltaTime);
    if(Occurrence == "Attack")Attack(entity, deltaTime);
    if(Occurrence == "Defend")Defend(entity, deltaTime);


}


void ResolveMovment::Walk(anax::Entity &entity, float deltaTime)
{
    TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
    AnimationComponent& animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.currentImage.y = animationComponent.row;
    animationComponent.totalTime += deltaTime;
    if(animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime)
    {
        animationComponent.currentImage.x = 3;
        animationComponent.changedDirection = false;

    }
    else if(animationComponent.totalTime >= animationComponent.switchTime)
    {
        animationComponent.totalTime -= animationComponent.switchTime;
        animationComponent.currentImage.x++;

        if (animationComponent.currentImage.x >= 11) {
            animationComponent.currentImage.x = 4;
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
    animationComponent.currentImage.x = 0;

    animationComponent.totalTime += deltaTime;

    //animationComponent.changedDirection = false;

    if(animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime)
    {
        animationComponent.currentImage.x = 0;
        animationComponent.changedDirection = false;

    }else if(animationComponent.totalTime >= animationComponent.switchTime) {
        animationComponent.totalTime -= animationComponent.switchTime;
        animationComponent.currentImage.x++;

        if (animationComponent.currentImage.x >= 3) {
            animationComponent.currentImage.x = 0;
        }
    }

    textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
    textureComponent.spriteRect.left = (animationComponent.currentImage.x +1)* abs(textureComponent.spriteRect.width);

}
void ResolveMovment::Attack(anax::Entity &entity, float deltaTime)
{
    bool attack = true;
    TextureComponent &textureComponent = entity.getComponent<TextureComponent>();
    AnimationComponent &animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.currentImage.y = animationComponent.row;

    while (attack) {

        animationComponent.totalTime += deltaTime;

        if (animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime) {
            animationComponent.currentImage.x = 11;
            animationComponent.changedDirection = false;

        } else if (animationComponent.totalTime >= animationComponent.switchTime) {
            animationComponent.totalTime -= animationComponent.switchTime;
            animationComponent.currentImage.x++;

            if (animationComponent.currentImage.x >= 15) {
                animationComponent.currentImage.x = 11;
                attack = false;
            }
            textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
            textureComponent.spriteRect.left = (animationComponent.currentImage.x + 1)* abs(textureComponent.spriteRect.width);
        }

    }
}
void ResolveMovment::Defend(anax::Entity &entity, float deltaTime)
{
    bool defend = true;
    TextureComponent &textureComponent = entity.getComponent<TextureComponent>();
    AnimationComponent &animationComponent = entity.getComponent<AnimationComponent>();
    animationComponent.currentImage.y = animationComponent.row;

    while (defend) {
        textureComponent.spriteRect.left = (animationComponent.currentImage.x + 1)* abs(textureComponent.spriteRect.width);

        animationComponent.totalTime += deltaTime;

        if (animationComponent.changedDirection && animationComponent.totalTime >= animationComponent.switchTime) {
            animationComponent.currentImage.x = 16;
            animationComponent.changedDirection = false;

        } else if (animationComponent.totalTime >= animationComponent.switchTime) {
            animationComponent.totalTime -= animationComponent.switchTime;
            animationComponent.currentImage.x++;

            if (animationComponent.currentImage.x >= 17) {
                animationComponent.currentImage.x = 16;
                defend = false;
            }
        }
    }
    textureComponent.spriteRect.top = animationComponent.currentImage.y* textureComponent.spriteRect.height;
}