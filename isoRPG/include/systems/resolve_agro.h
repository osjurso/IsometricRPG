//
// Created by Bjornar on 11/25/2017.
//

#ifndef ISORPG_RESOLVE_AGRO_H
#define ISORPG_RESOLVE_AGRO_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>




class ResolveAgro
{
public:
    ResolveAgro(){}

    void agro(anax::Entity player, anax::World& world);

};

#endif //ISORPG_RESOLVE_AGRO_H
