#include <components/Comp_Texture.h>
#include <components/Comp_Text.h>
#include <components/Comp_Dying.h>
#include <components/Comp_healt.h>
#include <components/Comp_lootable.h>
#include <components/Comp_UI.h>
#include <components/Comp_Parent.h>
#include <components/Comp_talk.h>
#include <systems/talk.h>
#include <systems/KillDialogues.h>
#include <include/components/CompCost.h>
#include <include/components/Comp_Menuchoice.h>
#include "collections/mouseClickedFunctions.h"
#include "components/Comp_Children.h"
#include "include/states/state_base.h"



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

void healthPunishment(anax::Entity &entity, anax::Entity &player, anax::World &world)
{
    player.getComponent<HealthComponent>().health -= 5;
}

void healthPotionReward(anax::Entity &entity, anax::Entity &player, anax::World &world)
{
    player.getComponent<Lootable>().HealthPotion += 1;
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


void BuyHealthPotion(anax::Entity &entity, anax::Entity &player, anax::World &world)
{

    if(player.getComponent<Lootable>().gold >= 50)
    {
        player.getComponent<Lootable>().gold -= 50;
        player.getComponent<Lootable>().HealthPotion += 1;
    }
}

void BuyArmorUpgrade(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    if(player.getComponent<Lootable>().gold >= player.getComponent<CostComponent>().ArmorUpgrade)
    {
        player.getComponent<Lootable>().gold -= player.getComponent<CostComponent>().ArmorUpgrade;
        player.getComponent<Lootable>().armor +=1;
        player.getComponent<CostComponent>().ArmorUpgrade += player.getComponent<CostComponent>().ArmorUpgrade;
        entity.getComponent<TextComponent>().content = "Upgrade Armor "+ std::to_string(player.getComponent<CostComponent>().ArmorUpgrade)+ "g";
        entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().optionMap[3] = entity.getComponent<TextComponent>().content;
        Update(entity,player,world);
    }
}

void BuyWeaponUpgrade(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    if(player.getComponent<Lootable>().gold >= player.getComponent<CostComponent>().WeaponUpgrade)
    {
        player.getComponent<Lootable>().gold -= player.getComponent<CostComponent>().WeaponUpgrade;
        player.getComponent<Lootable>().weapon +=1;
        player.getComponent<CostComponent>().WeaponUpgrade += player.getComponent<CostComponent>().WeaponUpgrade;
        entity.getComponent<TextComponent>().content = "Upgrade Weapon "+ std::to_string(player.getComponent<CostComponent>().WeaponUpgrade)+ "g";
        entity.getComponent<ParentComponent>().parent.getComponent<ParentComponent>().parent.getComponent<Talkative>().optionMap[4] = entity.getComponent<TextComponent>().content;
        Update(entity,player,world);
    }
}

void PayUp(anax::Entity& entity, anax::Entity& player, anax::World& world)
{
    player.getComponent<Lootable>().gold += (player.getComponent<HealthComponent>().unpaidKills*20);
    player.getComponent<HealthComponent>().unpaidKills = 0;
}

void setPlayOption(anax::Entity& entity)
{
    entity.getComponent<MenuChoiceComponent>().choice = "Game";
    std::cout << " pressed play" << std::endl;
}

void setNewCharacterOption(anax::Entity &entity)
{
    entity.getComponent<MenuChoiceComponent>().choice = "New";
    std::cout << " pressed new caracter" << std::endl;
}

void setSettingsOption(anax::Entity& entity)
{
    entity.getComponent<MenuChoiceComponent>().choice = "Settings";
}

void setAboutOption(anax::Entity& entity)
{
    entity.getComponent<MenuChoiceComponent>().choice = "About";
}

void setExitOption(anax::Entity& entity)
{
    entity.getComponent<MenuChoiceComponent>().choice = "Exit";
}

void setRenewOption(anax::Entity& entity)
{
    entity.getComponent<MenuChoiceComponent>().choice = "Renew";
    std::ofstream ofs;
    if(entity.getComponent<MenuChoiceComponent>().source == "delete1")
    {
        ofs.open("assets/saves/save1.txt", std::ofstream::out | std::ofstream::trunc);
    }
    if(entity.getComponent<MenuChoiceComponent>().source == "delete2")
    {
        ofs.open("assets/saves/save2.txt", std::ofstream::out | std::ofstream::trunc);
    }
    if(entity.getComponent<MenuChoiceComponent>().source == "delete3")
    {
        ofs.open("assets/saves/save3.txt", std::ofstream::out | std::ofstream::trunc);
    }

    ofs.close();
}