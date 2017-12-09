#include <components/Comp_Texture.h>
#include <components/Comp_Text.h>
#include <components/Comp_Dying.h>
#include <components/Comp_healt.h>
#include <components/Comp_looteble.h>
#include <components/Comp_UI.h>
#include <components/Comp_Parent.h>
#include <components/Comp_talk.h>
#include <systems/talk.h>
#include <systems/KillDialogs.h>
#include <include/components/CompCost.h>
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

void healtPunishment(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    player.getComponent<HealthComponent>().health -= 5;
}

void healtPotionRevard(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    player.getComponent<Looteble>().HealtPotion += 1;
}

void setDefault(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    killChildren(entity.getComponent<ParentComponent>().parent, player,world);
    entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().changeDialog = true;
    entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().Current = entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().Default;

}

void setInfo(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    killChildren(entity.getComponent<ParentComponent>().parent, player,world);
    entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().changeDialog = true;
    entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().Current = 0;
}

void Update(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    killChildren(entity.getComponent<ParentComponent>().parent, player,world);
    entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().changeDialog = true;
    entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().Current = 1;
}


void BuyHealtpotion(anax::Entity& entity, anax::Entity& player, anax::World& world)
{

    if(player.getComponent<Looteble>().gold >= 50)
    {
        player.getComponent<Looteble>().gold -= 50;
        player.getComponent<Looteble>().HealtPotion += 1;
    }
}

void BuyArmorUpgrade(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    if(player.getComponent<Looteble>().gold >= player.getComponent<CostComponent>().ArmorUpgrade)
    {
        player.getComponent<Looteble>().gold -= player.getComponent<CostComponent>().ArmorUpgrade;
        player.getComponent<Looteble>().armor +=1;
        player.getComponent<CostComponent>().ArmorUpgrade += player.getComponent<CostComponent>().ArmorUpgrade;
        entity.getComponent<TextComponent>().content = "Upgrade Armor "+ std::to_string(player.getComponent<CostComponent>().ArmorUpgrade)+ "g";
        entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().optionMap[3] = entity.getComponent<TextComponent>().content;
        Update(entity,player,world);
    }
}

void BuyWeaponUpgrade(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    if(player.getComponent<Looteble>().gold >= player.getComponent<CostComponent>().WeaponUpgrade)
    {
        player.getComponent<Looteble>().gold -= player.getComponent<CostComponent>().WeaponUpgrade;
        player.getComponent<Looteble>().weapon +=1;
        player.getComponent<CostComponent>().WeaponUpgrade += player.getComponent<CostComponent>().WeaponUpgrade;
        entity.getComponent<TextComponent>().content = "Upgrade Weapon "+ std::to_string(player.getComponent<CostComponent>().WeaponUpgrade)+ "g";
        entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().optionMap[4] = entity.getComponent<TextComponent>().content;
        Update(entity,player,world);
    }
}