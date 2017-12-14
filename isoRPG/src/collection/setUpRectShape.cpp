#include <components/Comp_SqureShape.h>
#include <components/Comp_Texture.h>
#include <components/Comp_position.h>
#include <components/Comp_size.h>
#include <components/Comp_State.h>
#include <components/Comp_Drawable.h>
#include "collections/setUpRectShape.h"

void SetUpRectShape::setUpRectShape(anax::Entity &entity, float xPos, float yPos, float Height, float Width, float zoom,
                                    sf::Color color, sf::View cam)
{
    entity.addComponent<SqureComponent>();
    SqureComponent& squreComponent = entity.getComponent<SqureComponent>();

    sf::Vector2f size;
    size.x = Height;
    size.y = Width;
    squreComponent.rectShape.setSize(size);
    squreComponent.rectShape.setFillColor(color);
    squreComponent.rectShape.setPosition(xPos,yPos);
    squreComponent.rectShape.setFillColor(color);

    entity.addComponent<TextureComponent>();
    entity.getComponent<TextureComponent>().sortKey = 1004;

    entity.addComponent<PositionComponent>();
    PositionComponent& positionComponent = entity.getComponent<PositionComponent>();

    //positionComponent.YPos = cam.getCenter().x - (cam.getSize().x/2) + entity.getComponent<UIComp>().xOffset;
    //positionComponent.XPos = cam.getCenter().y + (cam.getSize().y/2) + entity.getComponent<UIComp>().yOffset;

    positionComponent.XPos = cam.getCenter().x;
    positionComponent.YPos = cam.getCenter().y;
    positionComponent.SpriteLeft = positionComponent.XPos;
    positionComponent.SpriteTop = positionComponent.YPos;

    entity.addComponent<SizeComponent>();
    SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
    sizeComponent.Height = squreComponent.rectShape.getLocalBounds().height;
    sizeComponent.width = squreComponent.rectShape.getLocalBounds().width;
    sizeComponent.SpriteHeight = sizeComponent.Height;
    sizeComponent.SpriteWidth = sizeComponent.width;

    entity.addComponent<StateComponent>();
    StateComponent& stateComponent = entity.getComponent<StateComponent>();
    stateComponent.state = "Game";
    entity.addComponent<DrawableComponent>();
    entity.activate();
}