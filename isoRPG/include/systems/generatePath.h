
#ifndef ISORPG_GENERATEPATH_H
#define ISORPG_GENERATEPATH_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>


class GeneratePath
{
public:
    GeneratePath(){}

    void generate( anax::World& world, anax::Entity player);
};

#endif //ISORPG_GENERATEPATH_H
