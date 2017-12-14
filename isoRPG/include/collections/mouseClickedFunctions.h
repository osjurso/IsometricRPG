#ifndef ISORPG_MOUSECLIKEDFUNCTIONS_H
#define ISORPG_MOUSECLIKEDFUNCTIONS_H

#include <iostream>

#include <anax/Entity.hpp>

typedef void (*pfunc)(anax::Entity&, anax::Entity&, anax::World&);
void killChildren(anax::Entity& entity, anax::Entity& player, anax::World& world);

void healthPunishment(anax::Entity &entity, anax::Entity &player, anax::World &world);

void healthPotionReward(anax::Entity &entity, anax::Entity &player, anax::World &world);

void setDefault(anax::Entity& entity, anax::Entity& player, anax::World& world);

void BuyHealthPotion(anax::Entity &entity, anax::Entity &player, anax::World &world);

void BuyArmorUpgrade(anax::Entity& entity, anax::Entity& player, anax::World& world);

void BuyWeaponUpgrade(anax::Entity& entity, anax::Entity& player, anax::World& world);

void setInfo(anax::Entity& entity, anax::Entity& player, anax::World& world);

void setPlayOption(anax::Entity& entity);

void setSettingsOption(anax::Entity& entity);

void setAboutOption(anax::Entity& entity);

void setExitOption(anax::Entity& entity);

void setNewCharacterOption(anax::Entity &entity);

void setRenewOption(anax::Entity& entity);

void PayUp(anax::Entity& entity, anax::Entity& player, anax::World& world);
#endif //ISORPG_MOUSECLIKEDFUNCTIONS_H
