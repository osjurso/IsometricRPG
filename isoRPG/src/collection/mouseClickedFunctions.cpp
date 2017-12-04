#include <include/components/Comp_Texture.h>
#include <include/components/Comp_Text.h>
#include <include/components/Comp_Dying.h>
#include <include/components/Comp_healt.h>
#include <include/components/Comp_looteble.h>
#include <include/components/Comp_UI.h>
#include <include/components/Comp_Parent.h>
#include <include/components/Comp_talk.h>
#include "collections/mouseClikedFunctions.h"
#include "components/Comp_Children.h"


void killChildren(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    ChildComponent& childComponent = entity.getComponent<ChildComponent>();

    for(int i =0; i < childComponent.children.size(); i++)
    {
        anax::Entity& tempE = childComponent.children[i];

        if(tempE.hasComponent<DyingComponent>()) tempE.getComponent<DyingComponent>().dying = true;
    }
    if(entity.hasComponent<UIComp>())entity.getComponent<DyingComponent>().dying = true;
    if(entity.hasComponent<ParentComponent>())entity.getComponent<ParentComponent>().parent.getComponent<Talkative>().activeDialog = false;

}
void printFirst(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    std::cout << "Hello from first" << std::endl;

}
void printSecond(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    std::cout << "Hello from second" << std::endl;
}
void printThird(anax::Entity& entity, anax::Entity& player, anax::World& world)
{

    std::cout << "Hello from third" << std::endl;
}

void healtPunishment(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    player.getComponent<HealthComponent>().health -= 5;
}

void healtPotionRevard(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    player.getComponent<Looteble>().HealtPotion += 1;
}

