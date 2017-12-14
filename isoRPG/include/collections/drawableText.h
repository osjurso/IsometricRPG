
#ifndef ISORPG_DRAWEBLETEXT_H
#define ISORPG_DRAWEBLETEXT_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <states/state_base.h>
#include <application.h>

#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_animation.h>
#include <components/Comp_movable.h>
#include <components/Comp_healt.h>
#include <components/Comp_lootable.h>
#include <components/Comp_State.h>
#include <components/Comp_mousedOver.h>
#include <components/Comp_talk.h>
#include <components/Comp_UI.h>
#include <components/Comp_Text.h>
#include <components/Comp_Drawable.h>

class DrawableText
{
public:
    void setUpDrawableText(anax::Entity &entity, std::string content, sf::View &cam, std::string state, float zoom,
                           sf::Font &font, sf::Color color)
    {
        entity.addComponent<UIComp>();
        entity.addComponent<TextureComponent>();
        entity.getComponent<TextureComponent>().sortKey = 1003;

        entity.addComponent<TextComponent>();
        TextComponent& textComponent = entity.getComponent<TextComponent>();
        textComponent.font = font;
        textComponent.content = content;
        textComponent.text.setString(content);
        textComponent.text.setScale(zoom,zoom);
        textComponent.text.setFont(textComponent.font);
        textComponent.text.setFillColor(color);

        entity.addComponent<PositionComponent>();
        PositionComponent& positionComponent = entity.getComponent<PositionComponent>();
        positionComponent.XPos = cam.getCenter().x - (cam.getSize().x/2) + entity.getComponent<UIComp>().xOffset;
        positionComponent.YPos = cam.getCenter().y + (cam.getSize().y/2) + entity.getComponent<UIComp>().yOffset;
        positionComponent.SpriteLeft = positionComponent.XPos;
        positionComponent.SpriteTop = positionComponent.YPos;

        entity.addComponent<SizeComponent>();
        SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
        sizeComponent.Height = textComponent.text.getGlobalBounds().height +5;
        sizeComponent.width = textComponent.text.getGlobalBounds().width +5;
        sizeComponent.SpriteHeight = textComponent.text.getGlobalBounds().height +5;
        sizeComponent.SpriteWidth = textComponent.text.getGlobalBounds().width+ 5;


        entity.addComponent<StateComponent>();
        StateComponent& stateComponent = entity.getComponent<StateComponent>();
        stateComponent.state = state;

        entity.addComponent<DrawableComponent>();
        entity.activate();
    }
};

#endif //ISORPG_DRAWEBLETEXT_H
