#ifndef ISORPG_DRAWABLE_H
#define ISORPG_DRAWABLE_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>

#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>


class Draweble
{
public:
    void makeDraweble(sf::Texture& texture, int Left, int Top, anax::Entity& entity)
    {
        entity.addComponent<TextureComponent>();
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
        textureComponent.texture = texture;
        textureComponent.sprite.setTexture(texture);

        if (entity.hasComponent<Animated>()) {
            textureComponent.spriteRect.height = 128; //TODO: her må det vere mulig og sette in dynamisk, ville gjort det med og sende in noe til denne (makeDraweble)
            textureComponent.spriteRect.width = 128;
            textureComponent.spriteRect.top = 0;  //TODO: Det er denne og den under du må endre på en annen plass slik at den hopper rundt på texturen
            textureComponent.spriteRect.left = 0;
            textureComponent.sprite.setTextureRect(textureComponent.spriteRect);
        }

        entity.addComponent<PositionComponent>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        positionComponent.YPos = Top;
        positionComponent.XPos = Left;

        entity.addComponent<SizeComponent>();
        SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
        sizeComponent.Height = textureComponent.texture.getSize().x;
        sizeComponent.Whith = textureComponent.texture.getSize().y;
        entity.activate();
    }
};

#endif //ISORPG_DRAWABLE_H