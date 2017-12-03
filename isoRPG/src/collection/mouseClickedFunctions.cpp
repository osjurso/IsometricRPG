#include <include/components/Comp_Texture.h>
#include <include/components/Comp_Text.h>
#include <include/components/Comp_Dying.h>
#include "collections/mouseClikedFunctions.h"
#include "components/Comp_Children.h"


void killChildren(anax::Entity entity, anax::Entity player, anax::World& world)
{
    ChildComponent& childComponent = entity.getComponent<ChildComponent>();

    for(int i =0; i < childComponent.children.size(); i++)
    {
        anax::Entity& tempE = childComponent.children[i];

        if(tempE.hasComponent<DyingComponent>()) tempE.getComponent<DyingComponent>().dying = true;
        if(tempE.hasComponent<TextureComponent>())tempE.getComponent<TextureComponent>().draw = false;
        if(tempE.hasComponent<TextComponent>())tempE.getComponent<TextComponent>().draw = false;

    }
    entity.getComponent<TextureComponent>().draw = false;


}
void printFirst(anax::Entity entity, anax::Entity player, anax::World& world)
{
    std::cout << "Hello from first" << std::endl;
}
void printSecond(anax::Entity entity, anax::Entity player, anax::World& world)
{
    std::cout << "Hello from second" << std::endl;
}
void printThird(anax::Entity entity, anax::Entity player, anax::World& world)
{
    std::cout << "Hello from third" << std::endl;
}
