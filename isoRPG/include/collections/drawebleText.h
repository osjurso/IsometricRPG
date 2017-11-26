
#ifndef ISORPG_DRAWEBLETEXT_H
#define ISORPG_DRAWEBLETEXT_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <components/Comp_animation.h>
#include <components/Comp_moveble.h>
#include <components/Comp_healt.h>
#include <components/Comp_looteble.h>
#include <components/Comp_State.h>
#include <components/Comp_mousedOver.h>
#include <components/Comp_talk.h>
#include <include/components/Comp_UI.h>
#include <include/components/Comp_Text.h>

class DrawebleText
{
public:
    void setUpDrawebleText(anax::Entity& entity, std::string content, sf::View& cam, std::string state, float zoom, sf::Font& font, sf::Color color)
    {

        entity.addComponent<UIComp>();
        entity.addComponent<TextureComponent>();
        entity.getComponent<TextureComponent>().sortKey = 1002;

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
        positionComponent.YPos = cam.getCenter().x - (cam.getSize().x/2) + entity.getComponent<UIComp>().Xofset;;
        positionComponent.XPos = cam.getCenter().y + (cam.getSize().y/2) + entity.getComponent<UIComp>().Yofset;

        entity.addComponent<SizeComponent>();
        SizeComponent& sizeComponent = entity.getComponent<SizeComponent>();
        sizeComponent.Height = textComponent.text.getGlobalBounds().height;
        sizeComponent.Whith = textComponent.text.getGlobalBounds().width;


        entity.addComponent<StateComponent>();
        StateComponent& stateComponent = entity.getComponent<StateComponent>();
        stateComponent.state = state;
        entity.activate();

    }
};

#endif //ISORPG_DRAWEBLETEXT_H