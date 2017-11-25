
#ifndef ISORPG_RESOLVEPOSITIONCHANGE_H
#define ISORPG_RESOLVEPOSITIONCHANGE_H

#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>




class PostitonChange
{
public:
    PostitonChange(){}

    void change(anax::World& world);
private:
    void moveCreature(anax::Entity& entity);

};


#endif //ISORPG_RESOLVEPOSITIONCHANGE_H
