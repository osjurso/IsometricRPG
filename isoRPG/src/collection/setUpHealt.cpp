
#include <include/components/Comp_SqureShape.h>
#include <include/components/Comp_Texture.h>
#include <include/components/Comp_position.h>
#include <include/components/Comp_size.h>
#include <include/components/Comp_State.h>
#include "include/collections/setUpHealt.h"

void SetUpHealt::setUpHealt(anax::Entity& entity, float xPos,float yPos, float Height, float Width, float zoom, sf::Color color)
{
    entity.addComponent<SqureComponent>();
    SqureComponent& squreComponent = entity.getComponent<SqureComponent>();
    squreComponent.rectShape.setScale(Height*zoom,Width*zoom);
    squreComponent.rectShape.setFillColor(color);
    squreComponent.rectShape.setPosition(xPos,yPos);

    entity.addComponent<TextureComponent>();
    entity.getComponent<TextureComponent>().sortKey = 1002;

    entity.addComponent<PositionComponent>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
    positionComponent.XPos = squreComponent.rectShape.getLocalBounds().left;
    positionComponent.YPos = squreComponent.rectShape.getLocalBounds().top;
    positionComponent.SpriteLeft = positionComponent.XPos;
    positionComponent.SpriteTop = positionComponent.YPos;

    entity.addComponent<SizeComponent>();
    SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
    sizeComponent.Height = squreComponent.rectShape.getLocalBounds().height;
    sizeComponent.Whith = squreComponent.rectShape.getLocalBounds().width;
    sizeComponent.SpriteHeight = sizeComponent.Height;
    sizeComponent.SpriteWhith = sizeComponent.Whith;

    entity.addComponent<StateComponent>();
    StateComponent& stateComponent = entity.getComponent<StateComponent>();
    stateComponent.state = "Game";
    entity.activate();
}