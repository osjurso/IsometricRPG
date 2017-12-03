
#ifndef ISORPG_MOUSECLIKEDFUNCTIONS_H
#define ISORPG_MOUSECLIKEDFUNCTIONS_H
#include <iostream>
#include <anax/Entity.hpp>

typedef void (*pfunc)(anax::Entity&, anax::Entity&, anax::World&);

    void killChildren(anax::Entity& entity, anax::Entity& player, anax::World& world);

    void printFirst(anax::Entity& entity, anax::Entity& player, anax::World& world);

    void printSecond(anax::Entity& entity, anax::Entity& player, anax::World& world);

    void printThird(anax::Entity& entity, anax::Entity& player, anax::World& world);




#endif //ISORPG_MOUSECLIKEDFUNCTIONS_H
