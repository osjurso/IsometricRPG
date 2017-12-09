
#ifndef ISORPG_MOUSECLIKEDFUNCTIONS_H
#define ISORPG_MOUSECLIKEDFUNCTIONS_H
#include <iostream>
#include <anax/Entity.hpp>

typedef void (*pfunc)(anax::Entity&, anax::Entity&, anax::World&);
void killChildren(anax::Entity& entity, anax::Entity& player, anax::World& world);

void healtPunishment(anax::Entity& entity, anax::Entity& player, anax::World& world);

void healtPotionRevard(anax::Entity& entity, anax::Entity& player, anax::World& world);

void setDefault(anax::Entity& entity, anax::Entity& player, anax::World& world);

void BuyHealtpotion(anax::Entity& entity, anax::Entity& player, anax::World& world);

void BuyArmorUpgrade(anax::Entity& entity, anax::Entity& player, anax::World& world);

void BuyWeaponUpgrade(anax::Entity& entity, anax::Entity& player, anax::World& world);

void setInfo(anax::Entity& entity, anax::Entity& player, anax::World& world);




#endif //ISORPG_MOUSECLIKEDFUNCTIONS_H
