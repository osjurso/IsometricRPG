
#ifndef ISORPG_ADDDIALOGE_H
#define ISORPG_ADDDIALOGE_H


#include <anax/System.hpp>
#include <anax/anax.hpp>
#include <anax/World.hpp>

#include <states/state_base.h>
#include <application.h>
#include <SFML/Graphics/RenderWindow.hpp>


#include <include/components/Comp_size.h>
#include <components/Comp_position.h>
#include <components/Comp_Texture.h>
#include <include/components/Comp_animation.h>
#include <include/components/Comp_talk.h>


class AddDialoge
{
public:
    void addDialoge(anax::Entity& entity, std::string file, int index)
    {
        Talkative& talkative = entity.getComponent<Talkative>();
        talkative.Talkingfiles.insert(std::pair<int, std::string>(index, file));
        talkative.numberOfDialoges =+1;
    }
};

#endif //ISORPG_ADDDIALOGE_H
