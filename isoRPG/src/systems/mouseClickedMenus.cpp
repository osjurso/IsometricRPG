

#include <include/components/Comp_Text.h>
#include <include/collections/setUpRectShape.h>
#include "include/systems/mouseClickedMenus.h"

mouseClickedMenus::mouseClickedMenus(StateBase::Context context) :context(context)
{}

void mouseClickedMenus::Clicked()
{
    sf::RenderWindow& window = *context.window;
    anax::World& world = *context.world;
    sf::Mouse::getPosition(window).x;
    sf::Mouse::getPosition(window).y;
    auto enteties = world.getEntities();
    for(auto i : enteties)
    {
        if(i.hasComponent<MousedOver>())
        {
            process(i,sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y, window);
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
        entityRect.width =  e.getComponent<SizeComponent>().Whith ;

        entityRect.top =  positionComponent.YPos;
        entityRect.height = e.getComponent<SizeComponent>().Height;
/*
        anax::Entity temp = e.getWorld().createEntity();
        SetUpRectShape setUpRectShape;
        sf::View cam = window.getView();
        setUpRectShape.setUpRectshape(temp,entityRect.top,entityRect.left,entityRect.height,entityRect.width,1,sf::Color().White, cam);
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

