#ifndef ISORPG_DRAWABLE_H
#define ISORPG_DRAWABLE_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "states/state_base.h"
#include "application.h"

#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_animation.h>
#include <components/Comp_State.h>
#include <components/Comp_Drawable.h>


class Drawable
{
public:
    void makeDrawable(sf::Texture &texture, int Left, int Top, anax::Entity &entity, std::string state)
    {
        entity.addComponent<TextureComponent>();
        TextureComponent& textureComponent = entity.getComponent<TextureComponent>();
        textureComponent.texture[0] = texture;
        textureComponent.sprite[0].setTexture(texture);

        entity.addComponent<PositionComponent>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        positionComponent.XPos = Left;
        positionComponent.YPos = Top;

        entity.addComponent<SizeComponent>();
        SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
        sizeComponent.Height = textureComponent.texture[0].getSize().y;
        sizeComponent.width = textureComponent.texture[0].getSize().x;

        entity.addComponent<StateComponent>();
        StateComponent& stateComponent = entity.getComponent<StateComponent>();
        stateComponent.state = state;

        entity.addComponent<DrawableComponent>();
        entity.activate();
    }
};

#endif //ISORPG_DRAWABLE_H
