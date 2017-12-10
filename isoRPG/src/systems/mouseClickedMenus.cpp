

#include <include/components/Comp_Text.h>
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
    entityRect.top =  positionComponent.YPos - e.getComponent<TextComponent>().text.getLocalBounds().height/2;
    entityRect.left = positionComponent.XPos - e.getComponent<TextComponent>().text.getLocalBounds().width/2;
    entityRect.width =  e.getComponent<TextComponent>().text.getLocalBounds().width;
    entityRect.height = e.getComponent<TextComponent>().text.getLocalBounds().height;

    if(entityRect.contains(MouseX,MouseY))
    {
        if(e.hasComponent<AssosateFunc>())
        {
            anax::Entity entity;
            e.getComponent<AssosateFunc>().voidMenufunc(e);

        }
    }
}

