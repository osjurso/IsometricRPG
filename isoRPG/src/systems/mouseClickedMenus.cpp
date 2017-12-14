#include <components/Comp_Text.h>
#include "systems/mouseClickedMenus.h"

mouseClickedMenus::mouseClickedMenus(StateBase::Context context) :context(context)
{}

void mouseClickedMenus::Clicked()
{
    sf::RenderWindow& window = *context.window;
    anax::World& world = *context.world;
    sf::Vector2i mouse;
    mouse.x = sf::Mouse::getPosition(window).x;
    mouse.y = sf::Mouse::getPosition(window).y;

    sf::Vector2f mouseT = window.mapPixelToCoords(mouse, window.getView());
    //std::cout << sf::Mouse::getPosition(window).x << std::endl;

    auto entities = world.getEntities();
    for(auto i : entities)
    {
        if(i.hasComponent<MousedOver>())
        {
            process(i,mouseT.x,mouseT.y, window);
        }
    }


}
void mouseClickedMenus::process(anax::Entity &e, float MouseX, float MouseY, sf::RenderWindow &window)
{
    sf::IntRect entityRect;
    PositionComponent& positionComponent = e.getComponent<PositionComponent>();
    SizeComponent& sizeComponent = e.getComponent<SizeComponent>();


    if(e.hasComponent<TextComponent>())
    {
        entityRect.left = positionComponent.XPos ;
        entityRect.width =  e.getComponent<TextComponent>().text.getLocalBounds().width;

        entityRect.top =  positionComponent.YPos ;
        entityRect.height = e.getComponent<TextComponent>().text.getLocalBounds().height;
    }
    else
    {
        entityRect.left = positionComponent.XPos;
        entityRect.width =  e.getComponent<SizeComponent>().width ;

        entityRect.top =  positionComponent.YPos;
        entityRect.height = e.getComponent<SizeComponent>().Height;
/*
        anax::Entity temp = e.getWorld().createEntity();
        SetUpRectShape setUpRectShape;
        sf::View cam = window.getView();
        setUpRectShape.setUpRectShape(temp,entityRect.top,entityRect.left,entityRect.height,entityRect.width,1,sf::Color().White, cam);
        */
    }




    if(entityRect.contains(MouseX,MouseY))
    {
        if(e.hasComponent<AssosateFunc>())
        {
            e.getComponent<AssosateFunc>().voidMenufunc(e);

        }
    }
}

